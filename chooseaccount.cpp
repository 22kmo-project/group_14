#include "chooseaccount.h"
#include "ui_chooseaccount.h"

ChooseAccount::ChooseAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseAccount)
{
    ui->setupUi(this);
}

ChooseAccount::~ChooseAccount()
{
    delete ui;
}

void ChooseAccount::on_debitbutton_clicked()
{
   emit buttonClicked(2); // Moves stacked widget to index 2
}


void ChooseAccount::on_creditbutton_clicked()
{
    emit buttonClicked(2);

}

