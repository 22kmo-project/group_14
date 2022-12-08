#ifndef BALANCE_H
#define BALANCE_H
#include <QTableView>

#include "bankfunction.h"

#include <QWidget>

namespace Ui {
class Balance;
}

class Balance : public QWidget
{
    Q_OBJECT

public:
    explicit Balance(QWidget *parent = nullptr);
    ~Balance();

    void setBankFunction(BankFunction* bankFunction);

private:
    Ui::Balance *ui;
    void *transaction;
    void *cardtype;
    void *amount;
    void *date;
    int currentPage;
    int rows;

    BankFunction* bankFunction;

    

signals:
    void changeWidget(int);

private slots:
    void cancelButton();
    void updateTransactions();

    

    
};

#endif // BALANCE_H
