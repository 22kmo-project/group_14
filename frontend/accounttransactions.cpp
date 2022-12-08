#include "accounttransactions.h"
#include "ui_accounttransactions.h"

accountTransactions::accountTransactions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::accountTransactions)
{
    ui->setupUi(this);
    connect(ui->cancelButton, &QPushButton::clicked, this, &accountTransactions::cancelButton);
    connect(ui->nextpageButton, &QPushButton::clicked, this, &accountTransactions::nextpageButton);
    connect(ui->previouspageButton, &QPushButton::clicked, this, &accountTransactions::previouspageButton);

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

    currentPage = 1;
    rows = ui->tableWidget->rowCount();

    ui->tableWidget->setSortingEnabled(false);
}

accountTransactions::~accountTransactions()
{
    delete ui;
}

void accountTransactions::setBankFunction(BankFunction* bankFunction)
{
    this->bankFunction = bankFunction;
}

void accountTransactions::nextpageButton()
{
    if (bankFunction->GetTransactions().size() > currentPage * rows)
    {
        currentPage += 1;
        updateTransactions();
    }
}

void accountTransactions::previouspageButton()
{
    if (currentPage > 1)
    {
        currentPage -= 1;
        updateTransactions();
    }
}

void accountTransactions::cancelButton()
{
    emit changeWidget(2);
}

void accountTransactions::updateTransactions()
{
    ui->tableWidget->clearContents();
    QVector<TransactionData*> temp = bankFunction->GetTransactions();
    int startIndex = (currentPage - 1) * rows;
    int max = (currentPage - 1) * rows + rows;
    int r = 0;
    for (int i = startIndex; i < temp.size() && i < max; i++)
    {
        ui->tableWidget->setItem(r, 0, new QTableWidgetItem(temp[i]->eventType));
        ui->tableWidget->setItem(r, 1, new QTableWidgetItem(temp[i]->eventType));
        ui->tableWidget->setItem(r, 2, new QTableWidgetItem(temp[i]->amount));
        ui->tableWidget->setItem(r, 3, new QTableWidgetItem(temp[i]->dateTime));
        r += 1;
    }    
}
