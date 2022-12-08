#include "usermenu.h"
#include "ui_usermenu.h"
#include <QDebug>

UserMenu::UserMenu(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::UserMenu)
{
    ui->setupUi(this);
    connect(ui->button_cash, &QPushButton::clicked, this, &UserMenu::button_cash);
    connect(ui->button_deposit, &QPushButton::clicked, this, &UserMenu::button_deposit);
    connect(ui->button_donation, &QPushButton::clicked, this, &UserMenu::button_donation);
    connect(ui->button_balance, &QPushButton::clicked, this, &UserMenu::button_balance);
    connect(ui->button_transactions, &QPushButton::clicked, this, &UserMenu::button_transactions);
    connect(ui->button_logout, &QPushButton::clicked, this, &UserMenu::button_logout);
}

UserMenu::~UserMenu()
{
    delete ui;
}

void UserMenu::switchedToUserMenu(int type)
{
    accountType = type;
    qDebug() << "AccountMenuun siirrytty ->";
    qDebug() << "Account type selected (1=credit, 0=debit): " << accountType;
    getAccountInfo();
}

void UserMenu::getAccountInfo()
{
    QString cardId = "123456"; // Tähän taas pitäisi saada tuotua käytössä olevan kortin ID
    QString site_url = DatabaseURL::getBaseURL() + "/account/getinfo/" + cardId + "/" + QString::number(accountType);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    //request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    getAccountInfoManager = new QNetworkAccessManager(this);
    connect(getAccountInfoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getAccountInfoSlot(QNetworkReply*)));
    getAccountInfoReply = getAccountInfoManager->get(request);
}

void UserMenu::getAccountInfoSlot(QNetworkReply* getAccountInfoReply)
{
    QByteArray response_data = getAccountInfoReply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);

    // Saadaan käyttäjän nimet, saldo ja credit limitti
    QString customerName = jsonResponse["name"].toString();
    double balance = jsonResponse["balance"].toDouble();
    double creditLimit = jsonResponse["credit_limit"].toDouble();
    int accountId = jsonResponse["id_account"].toInt();
    qDebug() << "Name:" << customerName << "Balance:" << balance << "Credit limit:" << creditLimit << "Account ID:" << accountId;
    ui->textCustomerName->setText(customerName);

    getAccountInfoReply->deleteLater();
    getAccountInfoManager->deleteLater();
}


void UserMenu::button_logout()
{
    emit changeWidget(0);
    // joku emit homma tähän joka nollaisi login sivulla input fieldit
}

void UserMenu::button_balance()
{
    emit changeWidget(5);
    emit updateTransactions(1);
}

void UserMenu::button_transactions()
{
    emit changeWidget(6);
    emit updateTransactions(1);
}

void UserMenu::button_donation()
{
    emit changeWidget(4);
}

void UserMenu::button_cash()
{
    emit changeWidget(3);
}

void UserMenu::button_deposit()
{
    emit changeWidget(7);
}

void UserMenu::setCustomerName(QString name)
{
    ui->textCustomerName->setText(name);
}
