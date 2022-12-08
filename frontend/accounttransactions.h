#ifndef ACCOUNTTRANSACTIONS_H
#define ACCOUNTTRANSACTIONS_H


#include <QWidget>

#include "bankfunction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class accountTransactions; }
QT_END_NAMESPACE


class accountTransactions : public QWidget
{
    Q_OBJECT

public:
    explicit accountTransactions(QWidget *parent = nullptr);
    ~accountTransactions();

    void setBankFunction(BankFunction* bankFunction);

signals:
    void changeWidget(int);

private slots:
    void nextpageButton();
    void previouspageButton();
    void cancelButton();
    void updateTransactions();

private:

    Ui::accountTransactions *ui;
    int currentPage;
    int rows;

    BankFunction* bankFunction;
    
};

#endif // ACCOUNTTRANSACTIONS_H
