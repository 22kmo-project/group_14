#include "cashwithdrawal.h"
#include "ui_cashwithdrawal.h"

CashWithdrawal::CashWithdrawal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CashWithdrawal)
{
    ui->setupUi(this);
    connect(ui->button_confirm, &QPushButton::clicked, this, &CashWithdrawal::withdraw);
    connect(ui->button_back, &QPushButton::clicked, this, &CashWithdrawal::button_back);
}

CashWithdrawal::~CashWithdrawal()
{
    delete ui;
}

void CashWithdrawal::withdraw()
{
    QString id_account = "1"; // Tähän pitäisi saada tuotua valitun tilin id
    QString amount = "500"; // Ja tähän valittu nostosumma

    QJsonObject jsonObj;
    jsonObj.insert("id", id_account);
    jsonObj.insert("amount", amount);

    QString site_url=DatabaseURL::getBaseURL()+"/account/withdraw";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));
    reply = withdrawManager->post(request, QJsonDocument(jsonObj).toJson());
}

void CashWithdrawal::withdrawSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();
    QJsonDocument jsonResponseData = QJsonDocument::fromJson(responseData);

    bool success = jsonResponseData[0]["success"].toInt(); // success = 1 if transaction was made and 0 if it failed
    double balance = jsonResponseData[0]["balance"].toDouble();
    double creditLimit = jsonResponseData[0]["credit_limit"].toDouble();

    //qDebug() << jsonResponseData;
    //qDebug() << jsonResponseData[0];
    //int test = QString::compare(responseData, "false");

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
            if(success == 0)
            {
                qDebug();
                qDebug() << "Sorry. You have insufficient funds to complete this transaction.";
                qDebug() << "Your remaining balance is" << balance << "€.";

                if (creditLimit > 0) { // Jos kortti on credit, eli limitti > 0 niin voidaan halutessa tulostaa tiedoksi credit limittikin
                    qDebug() << "Your current credit limit is" << creditLimit << "€.";
                }
                // Vaihdetaan sitten stacked widgettiä cashWithdrawalin sisällä sivulle joka
                // näyttää virheilmoituksen sekä napin jolla voi palata näkymään jossa valitaan nostosumma
            }
            else
            {
                qDebug();
                qDebug() << "Your transaction is complete.";
                qDebug() << "Your remaining balance is" << balance << "€. Please take your cash and receipt.";

                if (creditLimit > 0) {
                    qDebug() << "Your current credit limit is" << creditLimit << "€.";
                }
                // Vaihdetaan näkymään jossa eri viesti sekä nappula (tai vaikka 5s automaattinen siirto) päävalikkoon(?)
            }
        }
    }

    reply->deleteLater();
    withdrawManager->deleteLater();
}

void CashWithdrawal::button_back()
{
    emit changeWidget(2);
}

void CashWithdrawal::button_otheramount()
{

}

void CashWithdrawal::button_20()
{

}

void CashWithdrawal::button_40()
{

}

void CashWithdrawal::button_50()
{

}

void CashWithdrawal::button_100()
{

}
