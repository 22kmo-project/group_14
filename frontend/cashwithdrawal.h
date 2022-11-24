#ifndef CASHWITHDRAWAL_H
#define CASHWITHDRAWAL_H

#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QString>
#include <QLineEdit>

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
    void button_back();
    void button_otheramount();
    void on_lineEdit_amount_selectionChanged();
    void button_confirm();
    void button_20();
    void button_40();
    void button_50();
    void button_100();

private:
    Ui::CashWithdrawal *ui;

signals:
    void changeWidget(int);
};

#endif // CASHWITHDRAWAL_H
