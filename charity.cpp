#include "charity.h"
#include "ui_charity.h"

charity::charity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::charity)
{
    ui->setupUi(this);
}

charity::~charity()
{
    delete ui;
}

void charity::on_button_confirm_clicked()
{
    emit buttonClicked(0);
}


void charity::on_button_cancel_clicked()
{
    emit buttonClicked(3);
}

