#include "creditordebit.h"
#include "ui_creditordebit.h"

creditordebit::creditordebit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creditordebit)
{
    ui->setupUi(this);
}

creditordebit::~creditordebit()
{
    delete ui;
}
