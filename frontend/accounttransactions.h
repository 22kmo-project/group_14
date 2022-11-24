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

signals:
    void buttonClicked(int);

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::accountTransactions *ui;
};

#endif // ACCOUNTTRANSACTIONS_H
