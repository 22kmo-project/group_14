#include "choosecredit.h"
#include "ui_choosecredit.h"

choosecredit::choosecredit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choosecredit)
{
    ui->setupUi(this);
}

choosecredit::~choosecredit()
{
    delete ui;
}
