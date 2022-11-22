#ifndef CHARITY_H
#define CHARITY_H

#include <QWidget>

namespace Ui {
class charity;
}

class charity : public QWidget
{
    Q_OBJECT

public:
    explicit charity(QWidget *parent = nullptr);
    ~charity();

private slots:
    void on_button_confirm_clicked();

    void on_button_cancel_clicked();

private:
    Ui::charity *ui;

signals:
    void buttonClicked(int);
};

#endif // CHARITY_H
