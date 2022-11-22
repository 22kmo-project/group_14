#ifndef ACCOUNTTRANSACTIONS_H
#define ACCOUNTTRANSACTIONS_H

#include <QWidget>

namespace Ui {
class accountTransactions;
}

class accountTransactions : public QWidget
{
    Q_OBJECT

public:
    explicit accountTransactions(QWidget *parent = nullptr);
    ~accountTransactions();

private:
    Ui::accountTransactions *ui;
};

#endif // ACCOUNTTRANSACTIONS_H
