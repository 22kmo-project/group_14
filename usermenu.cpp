#include "usermenu.h"
#include "ui_usermenu.h"

UserMenu::UserMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserMenu)
{
    ui->setupUi(this);
}

UserMenu::~UserMenu()
{
    delete ui;
}

void UserMenu::on_button_logout_clicked()
{
    emit buttonClicked(0);

}


void UserMenu::on_button_balance_clicked()
{
    emit buttonClicked(5);
}


void UserMenu::on_button_transactions_clicked()
{
    emit buttonClicked(6);
}


void UserMenu::on_button_donation_clicked()
{
    emit buttonClicked(4);
}


void UserMenu::on_button_cash_clicked()
{
    emit buttonClicked(3);
}

