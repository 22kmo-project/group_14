#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deposit)
{
    ui->setupUi(this);
    connect(ui->buttonBack, &QPushButton::clicked, this, &Deposit::buttonBack);
    connect(ui->buttonBills, &QPushButton::clicked, this, &Deposit::buttonBills);
    connect(ui->buttonCoins, &QPushButton::clicked, this, &Deposit::buttonCoins);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &Deposit::buttonCancel);
    connect(ui->buttonCancel2, &QPushButton::clicked, this, &Deposit::buttonCancel2);
    connect(ui->buttonContinue, &QPushButton::clicked, this, &Deposit::buttonContinue);
    connect(ui->buttonContinue2, &QPushButton::clicked, this, &Deposit::buttonContinue2);
    connect(ui->buttonConfirm, &QPushButton::clicked, this, &Deposit::buttonConfirm);
    connect(ui->buttonBills2, &QPushButton::clicked, this, &Deposit::buttonBills2);
    connect(ui->buttonCoins2, &QPushButton::clicked, this, &Deposit::buttonCoins2);
    connect(ui->buttonFinish, &QPushButton::clicked, this, &Deposit::buttonFinish);
}

Deposit::~Deposit()
{
    delete ui;
}

void Deposit::buttonConfirm()
{
    ui->stackedWidget->setCurrentIndex(3);
    emit makeDeposit();
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

void Deposit::buttonBack()
{
    emit changeWidget(2);
}

void Deposit::buttonBills()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(4);
}

void Deposit::buttonCoins()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(1);
}

void Deposit::buttonCancel()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(0);
}

void Deposit::buttonCancel2()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(0);
}

void Deposit::buttonContinue()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(2);
}

void Deposit::buttonContinue2()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(2);
}

void Deposit::buttonBills2()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(4);
}

void Deposit::buttonCoins2()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(1);
}

void Deposit::buttonFinish()
{
    ui->stackedWidget->setCurrentIndex(0);
    emit changeWidget(2);
}
