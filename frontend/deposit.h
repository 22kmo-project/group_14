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
    QNetworkReply *depositReply;
    QByteArray responseData;

private slots:
    void depositSlot(QNetworkReply* reply);
    void buttonBack();
    void buttonBills();
    void buttonCoins();
    void buttonCancel();
    void buttonCancel2();
    void buttonContinue();
    void buttonContinue2();
    void buttonConfirm();
    void buttonBills2();
    void buttonCoins2();
    void buttonFinish();

signals:
    void changeWidget(int);
};

#endif // DEPOSIT_H
