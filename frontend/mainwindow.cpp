#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bankFunction = new BankFunction();
    accountTransaction.setBankFunction(bankFunction);
    balance.setBankFunction(bankFunction);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginClicked);

    //Signal connections for changing between menus
    connect(&chooseAccount, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&userMenu, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&cashWithdrawal, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&charity, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&balance, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&accountTransaction, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&deposit, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(bankFunction, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));

    //Signal connections for resetting the timer for input timeouts that send the user back to either the usermenu or the login screen.
    connect(&accountTransaction, SIGNAL(resetTime()), this, SLOT(resetTimer()));
    connect(&charity, SIGNAL(resetTime()), this, SLOT(resetTimer()));
    connect(&deposit, SIGNAL(resetTime()), this, SLOT(resetTimer()));
    connect(&cashWithdrawal, SIGNAL(resetTime()), this, SLOT(resetTimer()));

    //Signal to either choose credit or debit type account for the user in case there are more than one accounts connected to the card.
    connect(&chooseAccount, SIGNAL(chooseAccountType(int)), &userMenu, SLOT(switchedToUserMenu(int)));

    connect(this, SIGNAL(login(QString, QString)), bankFunction, SLOT(requestLogin(QString, QString)));
    connect(bankFunction, SIGNAL(loginResult(int)), this, SLOT(loginResult(int)));

    connect(&cashWithdrawal, SIGNAL(setAmount(int)), bankFunction, SLOT(setMoneyAmount(int)));
    connect(&cashWithdrawal, SIGNAL(withdrawSignal()), bankFunction, SLOT(withdrawMoney()));
    connect(bankFunction, SIGNAL(withdrawalResult(int, double)), &cashWithdrawal, SLOT(withdrawSlot(int, double)));

    connect(&deposit, SIGNAL(setAmount(int)), bankFunction, SLOT(setMoneyAmount(int)));    
    connect(&deposit, SIGNAL(makeDeposit()), bankFunction, SLOT(depositMoney()));
    connect(bankFunction, SIGNAL(depositResult(int)), &deposit, SLOT(depositSlot(int)));

    connect(&charity, SIGNAL(setAmount(int)), bankFunction, SLOT(setMoneyAmount(int)));
    connect(&charity, SIGNAL(makeDonation()), bankFunction, SLOT(makeDonation()));
    connect(bankFunction, SIGNAL(donationResult(int)), &charity, SLOT(donationSlot(int)));

    connect(&userMenu, SIGNAL(updateTransactions(int)), bankFunction, SLOT(requestTransactions()));
    connect(bankFunction, SIGNAL(transactionsResult(int)), &accountTransaction, SLOT(updateTransactions()));

    connect(bankFunction, SIGNAL(transactionsResult(int)), &balance, SLOT(updateTransactions()));    

    connect(&chooseAccount, SIGNAL(chooseAccountType(int)), bankFunction, SLOT(setAccountType(int)));

    connect(bankFunction, SIGNAL(setCustomerName(QString)), &userMenu, SLOT(setCustomerName(QString)));

    ui->stackedWidget->insertWidget(1, &chooseAccount); // Lis??t????n tehdyt widgetit, eli yksitt??iset pankkiautomaatin n??kym??t, ja annetaan niille indeksit
    ui->stackedWidget->insertWidget(2, &userMenu);
    ui->stackedWidget->insertWidget(3, &cashWithdrawal);
    ui->stackedWidget->insertWidget(4, &charity);
    ui->stackedWidget->insertWidget(5, &balance);
    ui->stackedWidget->insertWidget(6, &accountTransaction);
    ui->stackedWidget->insertWidget(7, &deposit);

    QPixmap bkgnd("../img/background.png"); // These 5 lines sets background image to the window
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    ui->infoLabel->setVisible(0); // Hides error message container at start
    ui->idCardLine->setFocus(); // Sets focus to card number input field. Without this focus would be on pin code input.

    this->statusBar()->setSizeGripEnabled(false); // Hides resizing icon from bottom right corner
    this->setFixedSize(QSize(800, 600)); // Prevents resizing window

    ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), this, SLOT(timeComparison()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete bankFunction;
}

BankFunction* MainWindow::getBankFunction()
{
    return bankFunction;
}

void MainWindow::loginClicked()
{    
    QString idCard = ui->idCardLine->text();
    QString password = ui->passwordLine->text();

    emit login(idCard, password);
}

void MainWindow::moveToIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    time = 0;
    ptimer->start(1000);
}

void MainWindow::loginResult(int result)
{
    switch (result)
    {
        case 0: //Login failed because card number and pin didn't match
            ui->idCardLine->clear();
            ui->passwordLine->clear();
            ui->infoLabel->setVisible(1);
            ui->infoLabel->setText("Kortin numero ja tunnusluku eiv??t t??sm????.");
            break;
        case 1: //Login was successful
            ui->idCardLine->clear();
            ui->passwordLine->clear();
            ui->infoLabel->setVisible(0);
            ui->infoLabel->setText("");
            moveToIndex(1);
            break;
        case 2: //No response from server
            ui->infoLabel->setVisible(1);
            ui->infoLabel->setText("Server not responding");
            break;
        case 3: //Error in database connection returned
            ui->infoLabel->setVisible(1);
            ui->infoLabel->setText("Virhe tietokantayhteydess??.");
            break;
        case 4:
            ui->infoLabel->setVisible(1);
            ui->infoLabel->setText("Liian monta v????r???? yrityst??. Kortti on lukittu.");
            break;
        case 5://Login was successful, only debit account exists.
            ui->idCardLine->clear();
            ui->passwordLine->clear();
            ui->infoLabel->setVisible(0);
            ui->infoLabel->setText("");
            moveToIndex(2);
            break;
    }
}

void MainWindow::timeComparison()
{
    time++; //lasketaan aikaa
    if (ui->stackedWidget->currentIndex() == 1 && time > 10) {
        ui->stackedWidget->setCurrentIndex(0);
        ptimer->stop(); //Choose account n??kym??ss?? 10s aikaa valita credit tai debit
    }
    if (ui->stackedWidget->currentIndex() == 2 && time > 30) {
        ui->stackedWidget->setCurrentIndex(0);
        ptimer->stop(); //User menussa 30s niin kirjataan ulos
    }
    if (ui->stackedWidget->currentIndex() > 2 && time > 10) {
        ui->stackedWidget->setCurrentIndex(2);
        ptimer->stop();
        time = 0;
        ptimer->start();//Muissa n??kymiss?? 10s ja palataan user menuun
    }
}

void MainWindow::resetTimer()
{
    time = 0;
}
