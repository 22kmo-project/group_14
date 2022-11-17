#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QDialog>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

#include "databaseurl.h"


namespace Ui {
class StudentWindow;
}

class StudentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentWindow(QString idStudent, QWidget *parent = nullptr);
    ~StudentWindow();

    const QString &getWebToken() const;

    void setWebToken(const QString &newWebToken);

private slots:
    void studentInfoClicked();

    void studentGradesClicked();

    void gradeSlot(QNetworkReply* reply);

    void infoSlot(QNetworkReply* reply);

private:
    Ui::StudentWindow *ui;
    QString webToken;
    QString studentLoginID;

    QNetworkAccessManager* gradeManager;
    QNetworkAccessManager* infoManager;
    QNetworkReply* reply;
};

#endif // STUDENTWINDOW_H
