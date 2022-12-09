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
}

void UserMenu::getAccountInfo()
{

}

void UserMenu::getAccountInfoSlot(QNetworkReply* getAccountInfoReply)
{

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
