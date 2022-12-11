#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deposit)
{
    ui->setupUi(this);
    connect(ui->buttonBack, &QPushButton::clicked, this, &Deposit::buttonBack);
    connect(ui->buttonBack2, &QPushButton::clicked, this, &Deposit::buttonBack2);
    connect(ui->buttonConfirm, &QPushButton::clicked, this, &Deposit::buttonConfirm);
}

Deposit::~Deposit()
{
    delete ui;
}

void Deposit::buttonConfirm()
{
    ui->stackedWidget->setCurrentIndex(1);
    qDebug() << ui->amountInput->text();
    int amount = ui->amountInput->text().toInt();
    emit setAmount(amount);
    emit makeDeposit();
}

void Deposit::buttonBack()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->amountInput->clear();
    emit changeWidget(2);
}

void Deposit::buttonBack2()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->amountInput->clear();
    emit changeWidget(2);
}

void Deposit::depositSlot(int result)
{
    switch (result)
    {
    case 0:
        qDebug() << "Sorry. Something went wrong! Deposit failed.";
        break;
    case 1:
        qDebug() << "Deposit successful!";
        break;
    case 2:
        qDebug() << "Server not responding";
        break;
    case 3:
        qDebug() << "Error in database connection";
        break;
    }
}
