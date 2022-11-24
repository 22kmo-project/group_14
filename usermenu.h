#ifndef USERMENU_H
#define USERMENU_H

#include <QWidget>

namespace Ui {
class UserMenu;
}

class UserMenu : public QWidget
{
    Q_OBJECT

public:
    explicit UserMenu(QWidget *parent = nullptr);
    ~UserMenu();

private slots:


    void on_button_logout_clicked();

    void on_button_balance_clicked();

    void on_button_transactions_clicked();

    void on_button_donation_clicked();

    void on_button_cash_clicked();

private:
    Ui::UserMenu *ui;

signals:
    void buttonClicked(int);
};

#endif // USERMENU_H
