#include "charity.h"
#include "ui_charity.h"

charity::charity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::charity)
{
    ui->setupUi(this);
    connect(ui->button_confirm, &QPushButton::clicked, this, &charity::button_confirm);
    connect(ui->button_cancel, &QPushButton::clicked, this, &charity::button_cancel);
}

charity::~charity()
{
    delete ui;
}

void charity::button_confirm()
{
    emit changeWidget(5);
}


void charity::button_cancel()
{
    emit changeWidget(2);
}

