#ifndef CREDITORDEBIT_H
#define CREDITORDEBIT_H

#include <QDialog>

namespace Ui {
class creditordebit;
}

class creditordebit : public QDialog
{
    Q_OBJECT

public:
    explicit creditordebit(QWidget *parent = nullptr);
    ~creditordebit();

private:
    Ui::creditordebit *ui;
};

#endif // CREDITORDEBIT_H
