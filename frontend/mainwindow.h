#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include <QMainWindow>
#include "studentwindow.h"

#include <QtNetwork>
#include <QJsonObject>

#include "databaseurl.h"

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

private:
    Ui::MainWindow *ui;
    QPushButton* loginButton;

    StudentWindow *studentWindow;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray responseData;
    QString idCard;
};
#endif // MAINWINDOW_H
