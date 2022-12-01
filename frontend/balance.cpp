#include "balance.h"
#include "ui_balance.h"

Balance::Balance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Balance)
{
    ui->setupUi(this);
    connect(ui->cancelButton, &QPushButton::clicked, this, &Balance::cancelButton);

    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,150);

    QTableWidgetItem *transaction = new QTableWidgetItem("withdraw");
    QTableWidgetItem *cardtype = new QTableWidgetItem("debit");
    QTableWidgetItem *amount = new QTableWidgetItem("-100");
    QTableWidgetItem *date = new QTableWidgetItem("20.10.2022");

    ui->tableWidget->setItem(0,0,transaction);
    ui->tableWidget->setItem(0,1,cardtype);
    ui->tableWidget->setItem(0,2,amount);
    ui->tableWidget->setItem(0,3,date);

    //ui->tableWidget->setStyleSheet("background-color: transparent");

    ui->label_2->setText("2000,00 €");
}

Balance::~Balance()
{
    delete ui;
}

void Balance::cancelButton()
{
    emit changeWidget(2);
}
