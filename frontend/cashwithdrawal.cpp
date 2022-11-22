#include "cashwithdrawal.h"
#include "ui_cashwithdrawal.h"

CashWithdrawal::CashWithdrawal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CashWithdrawal)
{
    ui->setupUi(this);
    connect(ui->lineEdit_amount, &QLineEdit::textEdited, [this](const QString & text){
        ui->button_otheramount->setEnabled(!text.isEmpty());
    });
}

CashWithdrawal::~CashWithdrawal()
{
    delete ui;
}

void CashWithdrawal::on_button_back_clicked()
{
    emit buttonClicked(4);
}

void CashWithdrawal::on_button_otheramount_clicked()
{

}
