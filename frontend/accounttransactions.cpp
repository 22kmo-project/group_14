#include "accounttransactions.h"
#include "ui_accounttransactions.h"

accountTransactions::accountTransactions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::accountTransactions)
{
    ui->setupUi(this);
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
}

accountTransactions::~accountTransactions()
{
    delete ui;
}

void accountTransactions::on_pushButton_5_clicked()
{
    emit buttonClicked(3);
}


void accountTransactions::on_pushButton_6_clicked()
{

}


void accountTransactions::on_pushButton_7_clicked()
{

}


void accountTransactions::on_pushButton_10_clicked()
{
    emit buttonClicked(3);
}

