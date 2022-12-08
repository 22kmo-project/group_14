#ifndef CASHWITHDRAWAL_H
#define CASHWITHDRAWAL_H

#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QString>
#include <QtNetwork>
#include <QJsonObject>
#include "databaseurl.h"

namespace Ui {
class CashWithdrawal;
}

class CashWithdrawal : public QWidget
{
    Q_OBJECT

public:
    explicit CashWithdrawal(QWidget *parent = nullptr);
    ~CashWithdrawal();

private:
    Ui::CashWithdrawal *ui;
    QNetworkAccessManager *withdrawManager;
    QNetworkReply *reply;
    QByteArray responseData;
    int selectedAmount;

private slots:
    void withdrawSlot(int result, double balance);
    void withdraw();
    void button_back();
    void button_otheramount();
    void button_20();
    void button_40();
    void button_50();
    void button_100();
    void on_button_cancel2_clicked();
    void on_button_accept_clicked();
    void on_button_back_2_clicked();

signals:
    void changeWidget(int);
    void setAmount(int);
    void withdrawSignal();
};

#endif // CASHWITHDRAWAL_H
