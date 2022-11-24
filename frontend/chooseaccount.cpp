#include "chooseaccount.h"
#include "ui_chooseaccount.h"

ChooseAccount::ChooseAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseAccount)
{
    ui->setupUi(this);
    connect(ui->debitButton, &QPushButton::clicked, this, &ChooseAccount::debitButton);
    connect(ui->creditButton, &QPushButton::clicked, this, &ChooseAccount::creditButton);
}

ChooseAccount::~ChooseAccount()
{
    delete ui;
}

void ChooseAccount::debitButton()
{
    emit changeWidget(2);
}

void ChooseAccount::creditButton()
{
    emit changeWidget(2);
}

