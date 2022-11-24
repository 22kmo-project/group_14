#include "cashwithdrawal.h"
#include "ui_cashwithdrawal.h"


CashWithdrawal::CashWithdrawal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CashWithdrawal)
{
    ui->setupUi(this);
    connect(ui->button_confirm, &QPushButton::clicked, this, &CashWithdrawal::button_confirm);
    connect(ui->button_back, &QPushButton::clicked, this, &CashWithdrawal::button_back);
}

CashWithdrawal::~CashWithdrawal()
{
    delete ui;
}

void CashWithdrawal::button_back()
{
    emit changeWidget(2);
}

void CashWithdrawal::on_lineEdit_amount_selectionChanged()
{
    ui->lineEdit_amount->setDisabled(true);
}

void CashWithdrawal::button_otheramount()
{
    ui->lineEdit_amount->setEnabled(true);
}

void CashWithdrawal::button_confirm()
{
    emit changeWidget(4);
}

void CashWithdrawal::button_20()
{

}

void CashWithdrawal::button_40()
{

}

void CashWithdrawal::button_50()
{

}

void CashWithdrawal::button_100()
{

}
