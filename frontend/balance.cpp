#include "balance.h"
#include "ui_balance.h"

Balance::Balance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Balance)
{
    ui->setupUi(this);
    connect(ui->cancelButton, &QPushButton::clicked, this, &Balance::cancelButton);

    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,150);
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

    rows = ui->tableWidget->rowCount();
    currentPage = 1;
}

Balance::~Balance()
{
    delete ui;
}

void Balance::setBankFunction(BankFunction* bankFunction)
{
    this->bankFunction = bankFunction;
}

void Balance::updateTransactions()
{

    ui->balanceLabel->setText("Saldo: " + QString::number(bankFunction->getBalance())+ "€");
    if (bankFunction->getCreditLimit() > 0)
    {
        ui->creditLimitLabel->setText("Luottoraja: " + QString::number(bankFunction->getCreditLimit()) + "€");
    }
    else
    {
        ui->creditLimitLabel->setText("");
    }
    ui->customerNameLabel->setText(bankFunction->getCustomerName());

    ui->tableWidget->clearContents();
    QVector<TransactionData*> temp = bankFunction->GetTransactions();
    int startIndex = (currentPage - 1) * rows;
    int max = (currentPage - 1) * rows + rows;
    int r = 0;

    for (int i = startIndex; i < temp.size() && i < max; i++)
    {
        ui->tableWidget->setItem(r, 0, new QTableWidgetItem(temp[i]->transactionID));
        ui->tableWidget->setItem(r, 1, new QTableWidgetItem(temp[i]->eventType));
        ui->tableWidget->setItem(r, 2, new QTableWidgetItem(temp[i]->amount));
        ui->tableWidget->setItem(r, 3, new QTableWidgetItem(temp[i]->dateTime));
        r += 1;
    }
}

void Balance::cancelButton()
{
    emit changeWidget(2);
}
