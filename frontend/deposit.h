#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QString>
#include <QtNetwork>
#include <QJsonObject>
#include "databaseurl.h"

namespace Ui {
class Deposit;
}

class Deposit : public QWidget
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr);
    ~Deposit();

private:
    Ui::Deposit *ui;
    QNetworkAccessManager *depositManager;
    QNetworkReply *reply;
    QByteArray responseData;

private slots:
    void depositSlot(int result);
    void buttonBack();
    void buttonBack2();
    void buttonConfirm();

signals:
    void changeWidget(int);
    void makeDeposit();
    void resetTime();
    void setAmount(int);
};

#endif // DEPOSIT_H
