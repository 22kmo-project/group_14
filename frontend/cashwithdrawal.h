#ifndef CASHWITHDRAWAL_H
#define CASHWITHDRAWAL_H

#include <QWidget>

namespace Ui {
class CashWithdrawal;
}

class CashWithdrawal : public QWidget
{
    Q_OBJECT

public:
    explicit CashWithdrawal(QWidget *parent = nullptr);
    ~CashWithdrawal();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CashWithdrawal *ui;

signals:
    void buttonClicked(int);
};

#endif // CASHWITHDRAWAL_H
