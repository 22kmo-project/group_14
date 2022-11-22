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

void ChooseAccount::on_pushButton_2_clicked()
{
    emit buttonClicked(2); // Moves stacked widget to index 2
}

