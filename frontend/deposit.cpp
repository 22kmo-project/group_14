#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deposit)
{
    ui->setupUi(this);
    connect(ui->buttonBack, &QPushButton::clicked, this, &Deposit::buttonBack);
    connect(ui->buttonBills, &QPushButton::clicked, this, &Deposit::buttonBills);
    connect(ui->buttonCoins, &QPushButton::clicked, this, &Deposit::buttonCoins);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &Deposit::buttonCancel);
    connect(ui->buttonCancel2, &QPushButton::clicked, this, &Deposit::buttonCancel2);
    connect(ui->buttonContinue, &QPushButton::clicked, this, &Deposit::buttonContinue);
    connect(ui->buttonContinue2, &QPushButton::clicked, this, &Deposit::buttonContinue2);
    connect(ui->buttonConfirm, &QPushButton::clicked, this, &Deposit::buttonConfirm);
    connect(ui->buttonBills2, &QPushButton::clicked, this, &Deposit::buttonBills2);
    connect(ui->buttonCoins2, &QPushButton::clicked, this, &Deposit::buttonCoins2);
    connect(ui->buttonFinish, &QPushButton::clicked, this, &Deposit::buttonFinish);
}

Deposit::~Deposit()
{
    delete ui;
}

void Deposit::buttonConfirm()
{
    ui->stackedWidget->setCurrentIndex(3);

    QString id_account = "1";
    QString amount = QString::number(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/200))); // Random float number between 0.0 and 200

    QJsonObject jsonObj;
    jsonObj.insert("id", id_account);
    jsonObj.insert("amount", amount);

    QString site_url=DatabaseURL::getBaseURL()+"/account/deposit";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    depositManager = new QNetworkAccessManager(this);
    connect(depositManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(depositSlot(QNetworkReply*)));
    depositReply = depositManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Deposit::depositSlot(QNetworkReply *depositReply)
{
    responseData=depositReply->readAll();
    int test = QString::compare(responseData, "false");

    if(responseData.length() == 0)
    {
        qDebug() << "Server not responding";
    }
    else
    {
        if(QString::compare(responseData, "-4078") == 0)
        {
            qDebug() << "Error in database connection";
        }
        else
        {
            if(test == 0)
            {
                qDebug() << "Sorry. Something went wrong!";

            }
            else
            {
                qDebug() << "Deposit done!";
            }
        }
    }
}

void Deposit::buttonBack()
{
    emit changeWidget(2);
}

void Deposit::buttonBills()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Deposit::buttonCoins()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Deposit::buttonCancel()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Deposit::buttonCancel2()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Deposit::buttonContinue()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Deposit::buttonContinue2()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Deposit::buttonBills2()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Deposit::buttonCoins2()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Deposit::buttonFinish()
{
    ui->stackedWidget->setCurrentIndex(0);
    emit changeWidget(2);
}
