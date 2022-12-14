#ifndef CHARITY_H
#define CHARITY_H
#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QString>
#include <QLineEdit>
#include <QtNetwork>
#include <QJsonObject>
#include "databaseurl.h"

namespace Ui {
    class charity;
}

class charity : public QWidget
{
    Q_OBJECT

public:
    explicit charity(QWidget* parent = nullptr);
    ~charity();

private slots:
    void button_cancel();
    void donationSlot(int result);
    void donation();
    void on_button_kohde1_clicked();
    void on_button_kohde2_clicked();
    void on_button_kohde3_clicked();

private:
    Ui::charity* ui;
    QNetworkAccessManager* charityManager;
    QNetworkReply* reply;
    QByteArray responseData;
    int selectedAmount;
    QString charityName;

signals:
    void changeWidget(int);
    void makeDonation();
    void setAmount(int);
    void resetTime();
};

#endif // CHARITY_H
