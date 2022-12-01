#include "chooseaccount.h"
#include "ui_chooseaccount.h"
#include <QDebug>

ChooseAccount::ChooseAccount(QWidget *parent, int type) :
    QWidget(parent),
    ui(new Ui::ChooseAccount)
{
    ui->setupUi(this);
    qDebug() << "ChooseAccount created! Account type is:" << type;
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
    emit chooseAccountType(0);
}

void ChooseAccount::creditButton()
{
    emit changeWidget(2);
    emit chooseAccountType(1);
}
