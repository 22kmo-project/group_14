#include "studentwindow.h"
#include "qdebug.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(QString idStudent, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    ui->idStudentLabel->setText(idStudent);

    connect(ui->studentInfoButton, &QPushButton::clicked, this, &StudentWindow::studentInfoClicked);
    connect(ui->gradeButton, &QPushButton::clicked, this, &StudentWindow::studentGradesClicked);
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

const QString &StudentWindow::getWebToken() const
{
    return webToken;
}

void StudentWindow::setWebToken(const QString &newWebToken)
{
    webToken = newWebToken;
}

void StudentWindow::studentInfoClicked()
{
    QString wb = this->getWebToken();
    qDebug()<<"webtoken="+wb;
}

void StudentWindow::studentGradesClicked()
{
    QString wb = this->getWebToken();
    qDebug()<<"webtoken="+wb;

    QString site_url=DatabaseURL::getBaseURL()+"/studentgrade";



    //QString idStudent = ui->idStudentLine->text();
    //QString password = ui->passwordLine->text();

    QJsonObject jsonObj;
    //jsonObj.insert("id_student", idStudent);
    //jsonObj.insert("password", password);


    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //BASIC AUTENTIKOINTI ALKU
    QString credentials="admin:1234";
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    //BASIC AUTENTIKOINTI LOPPU

    gradeManager = new QNetworkAccessManager(this);
    connect(gradeManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(gradeSlot(QNetworkReply*)));

    reply = gradeManager->get(request);
}

void StudentWindow::gradeSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString grade;
    foreach (const QJsonValue &value, json_array)
    {
        QJsonObject json_obj = value.toObject();
        grade+=json_obj["name"].toString()+","+QString::number(json_obj["ects"].toInt())+","+QString::number(json_obj["grade"].toInt())+",";
    }

    qDebug()<<grade;

    ui->gradeLabel->setText(grade);

    reply->deleteLater();
    gradeManager->deleteLater();
}

void StudentWindow::infoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString info;
    foreach (const QJsonValue &value, json_array)
    {
        QJsonObject json_obj = value.toObject();
        info+=json_obj["name"].toString()+","+QString::number(json_obj["ects"].toInt())+","+QString::number(json_obj["grade"].toInt())+",";
    }

    qDebug()<<info;

    ui->studentInfoLabel->setText(info);

    //ui->updateFirstNameButton = json_obj["fname"].toString();

    reply->deleteLater();
    gradeManager->deleteLater();
}


