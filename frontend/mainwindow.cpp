#include "mainwindow.h"
#include "charity.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginClicked);

    connect(&chooseAccount, SIGNAL(buttonClicked(int)), this, SLOT(moveToIndex(int)));
    connect(&userMenu, SIGNAL(buttonClicked(int)), this, SLOT(moveToIndex(int)));
    connect(&cashWithdrawal, SIGNAL(buttonClicked(int)), this, SLOT(moveToIndex(int)));
    connect(&charity, SIGNAL(buttonClicked(int)), this, SLOT(moveToIndex(int)));



    ui->stackedWidget->insertWidget(1, &chooseAccount); // Lisätään tehdyt widgetit, eli yksittäiset pankkiautomaatin näkymät, ja annetaan niille indeksit
    ui->stackedWidget->insertWidget(2, &userMenu);
    ui->stackedWidget->insertWidget(3, &cashWithdrawal);
    ui->stackedWidget->insertWidget(4, &charity);

    QPixmap bkgnd("../img/background.png"); // These 5 lines sets background image to the window
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    ui->infoLabel->setVisible(0); // Hides error message container at start
    ui->idCardLine->setFocus(); // Sets focus to card number input field. Without this focus would be on pin code input.

    this->statusBar()->setSizeGripEnabled(false); // Hides resizing icon from bottom right corner
    this->setFixedSize(QSize(800, 600)); // Prevents resizing window
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginClicked()
{
    QString idCard = ui->idCardLine->text();
    QString password = ui->passwordLine->text();

    QJsonObject jsonObj;
    jsonObj.insert("id_card", idCard);
    jsonObj.insert("pin", password);

    QString site_url=DatabaseURL::getBaseURL()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();
    qDebug()<<responseData;
    int test = QString::compare(responseData, "false");
    qDebug()<<test;

    if(responseData.length()==0)
    {
        ui->infoLabel->setVisible(1);
        ui->infoLabel->setText("Server not responding");
       // ui->stackedWidget->setCurrentIndex(1); // Poista rivin kommentointi jos tietokantaserveri ei ole vielä toiminnassa ja haluat testata koodia.
    }
    else
    {
        if(QString::compare(responseData, "-4078")==0)
        {
            ui->infoLabel->setVisible(1);
            ui->infoLabel->setText("Error in database connection");
        }
        else
        {
            if(test == 0)
            {
                ui->idCardLine->clear();
                ui->passwordLine->clear();
                ui->infoLabel->setVisible(1);
                ui->infoLabel->setText("Card number and PIN code don't match");
            }
            else
            {
                ui->stackedWidget->setCurrentIndex(1);
            }
        }
    }
}

void MainWindow::moveToIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
