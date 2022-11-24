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
    void button_logout();
    void button_balance();
    void button_transactions();
    void button_donation();
    void button_cash();

private:
    Ui::UserMenu *ui;

signals:
    void changeWidget(int);
};

#endif // USERMENU_H
