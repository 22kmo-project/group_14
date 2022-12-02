#include "cashwithdrawal.h"
#include "ui_cashwithdrawal.h"


CashWithdrawal::CashWithdrawal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CashWithdrawal)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    connect(ui->button_confirm, &QPushButton::clicked, this, &CashWithdrawal::withdraw);
    connect(ui->button_back, &QPushButton::clicked, this, &CashWithdrawal::button_back);
    connect(ui->button_20, &QPushButton::clicked, this, &CashWithdrawal::button_20);
    connect(ui->button_40, &QPushButton::clicked, this, &CashWithdrawal::button_40);
    connect(ui->button_50, &QPushButton::clicked, this, &CashWithdrawal::button_50);
    connect(ui->button_100, &QPushButton::clicked, this, &CashWithdrawal::button_100);
    connect(ui->button_otheramount, &QPushButton::clicked, this, &CashWithdrawal::button_otheramount);
}

CashWithdrawal::~CashWithdrawal()
{
    delete ui;
}

void CashWithdrawal::withdraw()
{
    QString id_account = "1"; // Tähän pitäisi saada tuotua valitun tilin id
    QString amount = QString::number(selectedAmount); // Ja tähän valittu nostosumma

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
                qDebug() << "Sorry. You have insufficient funds available. Your current balance:" << balance << "Your credit limit:" << creditLimit;
                ui->stackedWidget->setCurrentIndex(2);
                // Vaihdetaan sitten stacked widgettiä cashWithdrawalin sisällä sivulle joka
                // näyttää virheilmoituksen sekä napin jolla voi palata näkymään jossa valitaan nostosumma
            }
            else
            {
                qDebug() << "Your transaction is complete. Your remaining balance is" << balance << "€. Please take your cash and receipt. Your credit limit:" << creditLimit;
                ui->stackedWidget->setCurrentIndex(0);
                // Vaihdetaan näkymään jossa eri viesti sekä nappula (tai vaikka 5s automaattinen siirto) päävalikkoon(?)
            }
        }
    }
}

void CashWithdrawal::button_back()
{
    emit changeWidget(2);
}

void CashWithdrawal::button_otheramount()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void CashWithdrawal::on_button_cancel2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void CashWithdrawal::on_button_accept_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    selectedAmount = (ui->lineEdit->text()).toInt();
}

void CashWithdrawal::button_20()
{
    selectedAmount = 20;
}

void CashWithdrawal::button_40()
{
    selectedAmount = 40;
}

void CashWithdrawal::button_50()
{
    selectedAmount = 50;
}

void CashWithdrawal::button_100()
{
    selectedAmount = 100;
}

void CashWithdrawal::on_button_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
