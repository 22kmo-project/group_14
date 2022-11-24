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
    explicit ChooseAccount(QWidget *parent = nullptr);
    ~ChooseAccount();

private:
    Ui::ChooseAccount *ui;

signals:
    void changeWidget(int);

private slots:
    void debitButton();
    void creditButton();
};

#endif // CHOOSEACCOUNT_H
