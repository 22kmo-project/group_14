#include "charity.h"
#include "ui_charity.h"

charity::charity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::charity)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->button_confirm, &QPushButton::clicked, this, &charity::donation);
    connect(ui->button_cancel, &QPushButton::clicked, this, &charity::button_cancel);
    connect(ui->button_kohde1, &QPushButton::clicked, this, &charity::on_button_kohde1_clicked);
    connect(ui->button_kohde2, &QPushButton::clicked, this, &charity::on_button_kohde2_clicked);
    connect(ui->button_kohde3, &QPushButton::clicked, this, &charity::on_button_kohde3_clicked);
}

charity::~charity()
{
    delete ui;
}

void charity::donation()
{
    QString id_account = "1"; // Tähän pitäisi saada tuotua valitun tilin id
    QString amount = QString::number(selectedAmount); // Ja tähän valittu nostosumma
    QString Value = QString::number(selectedAmount);

    QJsonObject jsonObj;
    jsonObj.insert("id", id_account);
    jsonObj.insert("amount", amount);
    jsonObj.insert("amount", Value);

    QString site_url=DatabaseURL::getBaseURL()+"/account/charity";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    charityManager = new QNetworkAccessManager(this);
    connect(charityManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(donationSlot(QNetworkReply*)));
    reply = charityManager->post(request, QJsonDocument(jsonObj).toJson());
}

void charity::donationSlot(QNetworkReply *reply)

{
    responseData=reply->readAll();
    int test = QString::compare(responseData, "false");

    if(responseData.length() == 0)
    {
        qDebug() << "Server not responding";
    }
    else
    {
        if(QString::compare(responseData, "-4078") == 0)
        {
            qDebug() << "Error in database connection";
        }
        else
        {
            if(test == 0)
            {
                qDebug() << "Error! Donation failed!.";
                ui->stackedWidget->setCurrentIndex(2);

                // Vaihdetaan sitten stacked widgettiä cashWithdrawalin sisällä sivulle joka
                // näyttää virheilmoituksen sekä napin jolla voi palata näkymään jossa valitaan nostosumma
            }
            else
            {
                qDebug() << "Donation completed successfully.";
                //emit changeWidget(2);
                ui->stackedWidget->setCurrentIndex(1);
                // Vaihdetaan näkymään jossa eri viesti sekä nappula (tai vaikka 5s automaattinen siirto) päävalikkoon(?)
            }
        }
    }
}

void charity::button_cancel()
{
    emit changeWidget(2);
}



void charity::on_button_kohde1_clicked()
{
    this->lineEdit();
}


void charity::on_button_kohde2_clicked()
{
    this->lineEdit();
}


void charity::on_button_kohde3_clicked()
{
    this->lineEdit();
}


void charity::lineEdit()
{
    selectedAmount = Value;

}

