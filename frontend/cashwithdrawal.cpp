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
    connect(ui->button_cancel2, &QPushButton::clicked, this, &CashWithdrawal::button_back2);
    connect(ui->button_back_2, &QPushButton::clicked, this, &CashWithdrawal::button_back2);
    connect(ui->buttonBack2, &QPushButton::clicked, this, &CashWithdrawal::button_back);
    selectedAmount = 20;
    ui->lineEdit->setText(QString::number(selectedAmount));
}

CashWithdrawal::~CashWithdrawal()
{
    delete ui;
}

void CashWithdrawal::withdraw()
{
    emit setAmount(selectedAmount);
    emit withdrawSignal();
}

void CashWithdrawal::withdrawSlot(int result, double balance)
{
    switch (result)
    {
    case 0:
        ui->stackedWidget->setCurrentIndex(2);
        ui->label_4->setText("Virhe. Tililläsi ei ole tarpeeksi katetta.\n\n Nykyinen saldosi on: " + QString::number(balance) + " €");
        break;
    case 1:
        ui->stackedWidget->setCurrentIndex(0);
        ui->label_3->setText("Nosto suoritettu onnistuneesti.\n\n Ota rahat ja kuitti!\n\n Nykyinen saldosi on " + QString::number(balance) + " €");
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
    emit resetTime();
    emit changeWidget(2);
    ui->stackedWidget->setCurrentIndex(1); // resets withdraw windows stacked widget index to first window
}

void CashWithdrawal::button_otheramount()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(3);
}

void CashWithdrawal::button_back2()
{
    emit resetTime();
    ui->stackedWidget->setCurrentIndex(1);
}

void CashWithdrawal::on_button_accept_clicked()
{
    selectedAmount = (ui->lineEdit->text()).toInt();
    emit setAmount(selectedAmount);
    emit withdrawSignal();
}

void CashWithdrawal::button_20()
{
    emit resetTime();
    selectedAmount = 20;
    emit setAmount(selectedAmount);
}

void CashWithdrawal::button_40()
{
    emit resetTime();
    selectedAmount = 40;
    emit setAmount(selectedAmount);
}

void CashWithdrawal::button_50()
{
    emit resetTime();
    selectedAmount = 50;
    emit setAmount(selectedAmount);
}

void CashWithdrawal::button_100()
{
    emit resetTime();
    selectedAmount = 100;
    emit setAmount(selectedAmount);
}
