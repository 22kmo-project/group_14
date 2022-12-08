#ifndef USERMENU_H
#define USERMENU_H

#include <QWidget>
#include "databaseurl.h"
#include <QMainWindow>
#include <QtNetwork>
#include <QJsonObject>

namespace Ui {
    class UserMenu;
}

class UserMenu : public QWidget
{
    Q_OBJECT

public:
    explicit UserMenu(QWidget* parent = nullptr);
    ~UserMenu();

private slots:
    void getAccountInfoSlot(QNetworkReply* getAccountInfoReply);
    void switchedToUserMenu(int);
    void button_logout();
    void button_balance();
    void button_transactions();
    void button_donation();
    void button_cash();
    void button_deposit();
    void setCustomerName(QString name);

private:
    Ui::UserMenu* ui;
    int accountType;
    void getAccountInfo();
    QNetworkAccessManager* getAccountInfoManager;
    QNetworkReply* getAccountInfoReply;
    QByteArray responseData;

signals:
    void changeWidget(int);
    void updateTransactions(int);
};

#endif // USERMENU_H

