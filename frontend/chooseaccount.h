#ifndef CHOOSEACCOUNT_H
#define CHOOSEACCOUNT_H

#include <QWidget>

namespace Ui {
class ChooseAccount;
}

class ChooseAccount : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseAccount(QWidget *parent = nullptr, int type = 2);
    ~ChooseAccount();

private:
    Ui::ChooseAccount *ui;

signals:
    void changeWidget(int);
    void chooseAccountType(int);

private slots:
    void debitButton();
    void creditButton();
};

#endif // CHOOSEACCOUNT_H
