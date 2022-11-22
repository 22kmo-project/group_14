#include "cashwithdrawal.h"
#include "ui_cashwithdrawal.h"

CashWithdrawal::CashWithdrawal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CashWithdrawal)
{
    ui->setupUi(this);
}

CashWithdrawal::~CashWithdrawal()
{
    delete ui;
}

void CashWithdrawal::on_pushButton_clicked()
{
    emit buttonClicked(4);
}

