#include "cashwithdrawal.h"
#include "ui_cashwithdrawal.h"


CashWithdrawal::CashWithdrawal(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CashWithdrawal)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    connect(ui->button_confirm, &QPushButton::clicked, this, &CashWithdrawal::withdraw);
    connect(ui->button_back, &QPushButton::clicked, this, &CashWithdrawal::button_back);
    connect(ui->button_20, &QPushButton::clicked, this, &CashWithdrawal::button_20);
    connect(ui->button_40, &QPushButton::clicked, this, &CashWithdrawal::button_40);
    connect(ui->button_50, &QPushButton::clicked, this, &CashWithdrawal::button_50);
    connect(ui->button_100, &QPushButton::clicked, this, &CashWithdrawal::button_100);
    connect(ui->button_otheramount, &QPushButton::clicked, this, &CashWithdrawal::button_otheramount);
}

CashWithdrawal::~CashWithdrawal()
{
    delete ui;
}

void CashWithdrawal::withdraw()
{
    emit withdrawSignal();
}

void CashWithdrawal::withdrawSlot(int result, double balance)
{
    switch (result)
    {
    case 0:
        ui->stackedWidget->setCurrentIndex(2);
        ui->label_4->setText("Sinulla ei ole tarpeeksi rahaa.\n\n Nykyinen saldosi on: " + QString::number(balance) + " €");
        break;
    case 1:
        ui->stackedWidget->setCurrentIndex(0);
        ui->label_3->setText("Tapahtuma on suoritettu.\n\n Ota rahat ja kuitti!\n\n Nykyinen saldosi on " + QString::number(balance) + " €");
        break;
    case 2:
        qDebug() << "Server not responding";
        break;
    case 3:
        qDebug() << "Error in database connection";
        break;
    }
}

void CashWithdrawal::button_back()
{
    emit changeWidget(2);
}

void CashWithdrawal::button_otheramount()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void CashWithdrawal::on_button_cancel2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void CashWithdrawal::on_button_accept_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    selectedAmount = (ui->lineEdit->text()).toInt();
    emit setAmount(selectedAmount);
}

void CashWithdrawal::button_20()
{
    selectedAmount = 20;
    emit setAmount(selectedAmount);
}

void CashWithdrawal::button_40()
{
    selectedAmount = 40;
    emit setAmount(selectedAmount);
}

void CashWithdrawal::button_50()
{
    selectedAmount = 50;
    emit setAmount(selectedAmount);
}

void CashWithdrawal::button_100()
{
    selectedAmount = 100;
    emit setAmount(selectedAmount);
}


void CashWithdrawal::on_button_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}