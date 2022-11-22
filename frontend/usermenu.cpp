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

void UserMenu::on_pushButton_3_clicked()
{
    emit buttonClicked(3);
}

