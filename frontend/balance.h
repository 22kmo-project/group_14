#ifndef BALANCE_H
#define BALANCE_H
#include <QTableView>

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

private:
    Ui::Balance *ui;
    void *transaction;
    void *cardtype;
    void *amount;
    void *date;

signals:
    void buttonClicked(int);
private slots:
    void on_pushButton_4_clicked();
};

#endif // BALANCE_H
