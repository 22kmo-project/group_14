#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginClicked);

    QPixmap bkgnd("../img/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginClicked()
{
    QString idCard = ui->idCardLine->text();
    QString password = ui->passwordLine->text();

    QJsonObject jsonObj;
    jsonObj.insert("id_card", idCard);
    jsonObj.insert("pin", password);

    QString site_url=DatabaseURL::getBaseURL()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();
    qDebug()<<responseData;
    int test = QString::compare(responseData, "false");
    qDebug()<<test;

    if(responseData.length()==0)
    {
        ui->infoLabel->setText("Server not responding");
    }
    else
    {
        if(QString::compare(responseData, "-4078")==0)
        {
            ui->infoLabel->setText("Error in database connection");
        }
        else
        {
            if(test == 0)
            {
                ui->idCardLine->clear();
                ui->passwordLine->clear();
                ui->infoLabel->setText("Card number and PIN code don't match");
            }
            else
            {
                //qDebug()<< "Test wasn't 0" << test;
                studentWindow=new StudentWindow(idCard);
                studentWindow->setWebToken(responseData);
                studentWindow->show();
            }
        }
    }

}




