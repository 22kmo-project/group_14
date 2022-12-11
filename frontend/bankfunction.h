#ifndef BANKFUNCTION_H
#define BANKFUNCTION_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QtNetwork>
#include <QJsonObject>
#include "databaseurl.h"
//#include "mainwindow.h"

#include <QJsonValue>

//Struct for holding data for each transaction made by an account
struct TransactionData
{
    QString transactionID;
    QString accountID;
    QString dateTime;
    QString eventType;
    QString amount;
};

class BankFunction : public QObject
{
    Q_OBJECT
public:
    explicit BankFunction(QObject *parent = nullptr);
    ~BankFunction();

    QByteArray getLoginToken();

    void requestCustomer();

    QVector<TransactionData*> GetTransactions();

    void logOut();

    double getBalance();
    int getCreditLimit();
    QString getCustomerName();

private slots:
    void requestLogin(QString id_card, QString pin);
    void processLogin(QNetworkReply* reply);

    void processCustomer(QNetworkReply* reply);

    void withdrawMoney();
    void processWithdrawal(QNetworkReply* reply);

    void depositMoney();
    void processDeposit(QNetworkReply* reply);

    void requestTransactions();
    void processTransactions();

    void makeDonation();
    void processDonation(QNetworkReply* reply);

    void setAccountId(int accountId);
    void setMoneyAmount(int moneyAmount);

    void getAccountInfo();
    void processAccountInfo(QNetworkReply* reply);
    void setAccountType(int type);

    void numAccountSlot(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkAccessManager;

    int accountId;
    int accountType;
    int cardId;
    double moneyAmount;

    double balance;
    int creditLimit;

    int customerId;
    QString customerName;

    QVector<TransactionData*> transactions;
    QString url;
    QNetworkReply* reply;
    QByteArray responseData;
    QByteArray loginToken;

    void getNumberOfAccounts();

signals:
    void loginResult(int);
    void transactionsResult(int);
    void withdrawalResult(int result, double remainingBalance = 0.0);
    void donationResult(int);
    void setCustomerName(QString name);
    void depositResult(int);
    void changeWidget(int);

};

#endif // BANKFUNCTION_H
