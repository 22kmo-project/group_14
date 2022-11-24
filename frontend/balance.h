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
    void changeWidget(int);

private slots:
    void cancelButton();
};

#endif // BALANCE_H
