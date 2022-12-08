#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include <QMainWindow>
#include <QtNetwork>
#include <QJsonObject>
#include "databaseurl.h"
#include <usermenu.h>
#include <chooseaccount.h>
#include <cashwithdrawal.h>
#include <charity.h>
#include <balance.h>
#include <accounttransactions.h>
#include <deposit.h>
#include "bankfunction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class BankFunction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    BankFunction* getBankFunction();

private slots:
    void loginClicked();
    //void loginSlot(QNetworkReply* reply);
    void moveToIndex(int index);
    void loginResult(int result);
    void timeComparison();

private:
    Ui::MainWindow *ui;
    QPushButton* loginButton;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray responseData;
    QString idCard;
    QTimer* ptimer;
    int time;
    
    ChooseAccount chooseAccount;
    UserMenu userMenu;
    CashWithdrawal cashWithdrawal;
    charity charity;
    Balance balance;
    accountTransactions accountTransaction;
    Deposit deposit;
    
    BankFunction* bankFunction;

signals:
    void login(QString, QString);
};
#endif // MAINWINDOW_H
