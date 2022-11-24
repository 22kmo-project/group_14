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
    void on_button_back_clicked();

    void on_button_otheramount_clicked();

    void on_lineEdit_amount_selectionChanged();

    void on_button_confirm_clicked();

    void on_button_20_clicked();

    void on_button_40_clicked();

    void on_button_50_clicked();

    void on_button_100_clicked();

private:
    Ui::CashWithdrawal *ui;

signals:
    void buttonClicked(int);
};

#endif // CASHWITHDRAWAL_H
