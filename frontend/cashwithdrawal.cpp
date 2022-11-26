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
                qDebug() << "Sorry. You have insufficient funds available.";
                // Vaihdetaan sitten stacked widgettiä cashWithdrawalin sisällä sivulle joka
                // näyttää virheilmoituksen sekä napin jolla voi palata näkymään jossa valitaan nostosumma
            }
            else
            {
                qDebug() << "Your transaction is complete. Your remaining balance is X €. Please take your cash and receipt.";
                // Vaihdetaan näkymään jossa eri viesti sekä nappula (tai vaikka 5s automaattinen siirto) päävalikkoon(?)
            }
        }
    }
}

void CashWithdrawal::button_back()
{
    emit changeWidget(2);
}

void CashWithdrawal::on_lineEdit_amount_selectionChanged()
{
    ui->lineEdit_amount->setDisabled(true);
}

void CashWithdrawal::button_otheramount()
{
    ui->lineEdit_amount->setEnabled(true);
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
