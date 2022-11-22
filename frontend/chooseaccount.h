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
    void buttonClicked(int);

private slots:
    void on_pushButton_2_clicked();
};

#endif // CHOOSEACCOUNT_H
