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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loginClicked();
    void loginSlot(QNetworkReply* reply);
    void testSlot(QNetworkReply *reply);
    void moveToIndex(int);

private:
    void getNumberOfAccounts();
    Ui::MainWindow *ui;
    QPushButton* loginButton;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *testManager;
    QNetworkReply *reply;
    QByteArray responseData;
    QString idCard;

    ChooseAccount chooseAccount;
    UserMenu userMenu;
    CashWithdrawal cashWithdrawal;
    charity charity;
    Balance balance;
    accountTransactions accountTransaction;
    Deposit deposit;
};
#endif // MAINWINDOW_H
