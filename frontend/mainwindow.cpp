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

    connect(&chooseAccount, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&userMenu, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&cashWithdrawal, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&charity, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&balance, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&accountTransaction, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(&deposit, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));
    connect(bankFunction, SIGNAL(changeWidget(int)), this, SLOT(moveToIndex(int)));

    connect(&chooseAccount, SIGNAL(chooseAccountType(int)), &userMenu, SLOT(switchedToUserMenu(int)));

    connect(this, SIGNAL(login(QString, QString)), bankFunction, SLOT(requestLogin(QString, QString)));
    connect(bankFunction, SIGNAL(loginResult(int)), this, SLOT(loginResult(int)));

    connect(&cashWithdrawal, SIGNAL(setAmount(int)), bankFunction, SLOT(setMoneyAmount(int)));
    connect(&cashWithdrawal, SIGNAL(withdrawSignal()), bankFunction, SLOT(withdrawMoney()));
    connect(bankFunction, SIGNAL(withdrawalResult(int, double)), &cashWithdrawal, SLOT(withdrawSlot(int, double)));

    connect(bankFunction, SIGNAL(depositResult(int)), &deposit, SLOT(depositSlot(int)));
    connect(&deposit, SIGNAL(makeDeposit()), bankFunction, SLOT(depositMoney()));

    connect(&charity, SIGNAL(setAmount(int)), bankFunction, SLOT(setMoneyAmount(int)));
    connect(&charity, SIGNAL(makeDonation()), bankFunction, SLOT(makeDonation()));
    connect(bankFunction, SIGNAL(donationResult(int)), &charity, SLOT(donationSlot(int)));

    connect(&userMenu, SIGNAL(updateTransactions(int)), bankFunction, SLOT(requestTransactions()));
    connect(bankFunction, SIGNAL(transactionsResult(int)), &accountTransaction, SLOT(updateTransactions()));

    connect(bankFunction, SIGNAL(transactionsResult(int)), &balance, SLOT(updateTransactions()));
    
    

    connect(&chooseAccount, SIGNAL(chooseAccountType(int)), bankFunction, SLOT(setAccountType(int)));

    connect(bankFunction, SIGNAL(setCustomerName(QString)), &userMenu, SLOT(setCustomerName(QString)));



    ui->stackedWidget->insertWidget(1, &chooseAccount); // Lisätään tehdyt widgetit, eli yksittäiset pankkiautomaatin näkymät, ja annetaan niille indeksit
    ui->stackedWidget->insertWidget(2, &userMenu);
    ui->stackedWidget->insertWidget(3, &cashWithdrawal);
    ui->stackedWidget->insertWidget(4, &charity);
    ui->stackedWidget->insertWidget(5, &balance);
    ui->stackedWidget->insertWidget(6, &accountTransaction);
    ui->stackedWidget->insertWidget(7, &deposit);

    QPixmap bkgnd("img/background.png"); // These 5 lines sets background image to the window
   // QPixmap bkgnd("../img/background.png"); // These 5 lines sets background image to the window
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
    //bankFunction->requestLogin(idCard, password);
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
            ui->infoLabel->setText("Card number and PIN code don't match");
            break;
        case 1: //Login was successful
            ui->idCardLine->clear();
            ui->passwordLine->clear();
            moveToIndex(1);
            break;
        case 2: //No response from server
            ui->infoLabel->setVisible(1);
            ui->infoLabel->setText("Server not responding");
            break;
        case 3: //Error in database connection returned
            ui->infoLabel->setVisible(1);
            ui->infoLabel->setText("Error in database connection");
            break;
        case 4:
            ui->infoLabel->setVisible(1);
            ui->infoLabel->setText("Liian monta väärää yritystä. Kortti on lukittu.");
            break;
    }
}

void MainWindow::timeComparison()
{
    //qDebug() << "lasketaan";
    time++; //lasketaan aikaa
    //qDebug() << time;

    if (ui->stackedWidget->currentIndex() == 1 && time > 10) {
        ui->stackedWidget->setCurrentIndex(0);
        ptimer->stop(); //Choose account näkymässä 10s aikaa valita credit tai debit
    }
    if (ui->stackedWidget->currentIndex() == 2 && time > 30) {
        ui->stackedWidget->setCurrentIndex(0);
        ptimer->stop(); //User menussa 30s niin kirjataan ulos
    }
    if (ui->stackedWidget->currentIndex() > 2 && time > 10) {
        ui->stackedWidget->setCurrentIndex(2);
        ptimer->stop();
        time = 0;
        ptimer->start();//Muissa näkymissä 10s ja palataan user menuun
    }
}