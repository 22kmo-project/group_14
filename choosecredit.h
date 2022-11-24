#ifndef CHOOSECREDIT_H
#define CHOOSECREDIT_H

#include <QDialog>

namespace Ui {
class choosecredit;
}

class choosecredit : public QDialog
{
    Q_OBJECT

public:
    explicit choosecredit(QWidget *parent = nullptr);
    ~choosecredit();

private:
    Ui::choosecredit *ui;
};

#endif // CHOOSECREDIT_H
