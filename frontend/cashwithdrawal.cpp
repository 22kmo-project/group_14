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


void CashWithdrawal::on_button_back_clicked()
{
    emit buttonClicked(4);
}


void CashWithdrawal::on_lineEdit_amount_selectionChanged()
{
    ui->lineEdit_amount->setDisabled(true);
}


void CashWithdrawal::on_button_otheramount_clicked()
{
    ui->lineEdit_amount->setEnabled(true);
}



void CashWithdrawal::on_button_confirm_clicked()
{
    emit buttonClicked(0);
}


void CashWithdrawal::on_button_20_clicked()
{

}


void CashWithdrawal::on_button_40_clicked()
{

}


void CashWithdrawal::on_button_50_clicked()
{

}


void CashWithdrawal::on_button_100_clicked()
{

}

