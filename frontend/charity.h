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
    void button_confirm();
    void button_cancel();

private:
    Ui::charity *ui;

signals:
    void changeWidget(int);
};

#endif // CHARITY_H
