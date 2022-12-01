#include "usermenu.h"
#include "ui_usermenu.h"
#include <QDebug>

UserMenu::UserMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserMenu)
{
    ui->setupUi(this);
    qDebug() << "UserMenu created!! Testing 2: ";
    connect(ui->button_cash, &QPushButton::clicked, this, &UserMenu::button_cash);
    connect(ui->button_donation, &QPushButton::clicked, this, &UserMenu::button_donation);
    connect(ui->button_balance, &QPushButton::clicked, this, &UserMenu::button_balance);
    connect(ui->button_transactions, &QPushButton::clicked, this, &UserMenu::button_transactions);
    connect(ui->button_logout, &QPushButton::clicked, this, &UserMenu::button_logout);
    connect(ui->button_deposit, &QPushButton::clicked, this, &UserMenu::button_deposit);
}

UserMenu::~UserMenu()
{
    delete ui;
}

void UserMenu::button_logout()
{
    emit changeWidget(0);
}

void UserMenu::button_balance()
{
    emit changeWidget(5);
}

void UserMenu::button_transactions()
{
    emit changeWidget(6);
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

void UserMenu::getAccountType(int type)
{
    accountType = type;
    qDebug() << "TESTING";
    qDebug() << "Account type: " << accountType;
}

