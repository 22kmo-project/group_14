#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include <QMainWindow>
#include "studentwindow.h"
#include <QtNetwork>
#include <QJsonObject>
#include "databaseurl.h"

#include <usermenu.h>
#include <chooseaccount.h>
#include <cashwithdrawal.h>
#include <charity.h>

#include <balance.h>

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
    void moveToIndex(int);

private:
    Ui::MainWindow *ui;
    QPushButton* loginButton;

    StudentWindow *studentWindow;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray responseData;
    QString idCard;

    ChooseAccount chooseAccount;
    UserMenu userMenu;
    CashWithdrawal cashWithdrawal;
    charity charity;
    Balance balance;
};
#endif // MAINWINDOW_H
