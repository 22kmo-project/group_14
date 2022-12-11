#include "bankfunction.h"

BankFunction::BankFunction(QObject *parent)
    : QObject{parent}
{
    //Set accountId to 1 by default, remove when logging in changes this value
    accountId = 1;
    cardId = 1;
    customerId = 1;
    moneyAmount = 0.0;
}

BankFunction::~BankFunction()
{
    //delete networkAccessManager;

    for (int i = transactions.size()-1; i >= 0; i--)
    {
         delete transactions.at(i);
    }
}

//HTTP request for logging in, parameters for logging in are passed in QString format
void BankFunction::requestLogin(QString id_card, QString pin)
{
    networkAccessManager = new QNetworkAccessManager(this);
    QJsonObject jsonObj;
    jsonObj.insert("id_card", id_card);
    jsonObj.insert("pin", pin);

    cardId = id_card.toInt();

    url = DatabaseURL::getBaseURL() + "/login";

    QNetworkRequest request((url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processLogin(QNetworkReply*)));

    reply = networkAccessManager->post(request, QJsonDocument(jsonObj).toJson());
}

QByteArray BankFunction::getLoginToken()
{
    return loginToken;
}

//Handles data got from a QNetworkReply object to see if login was successful.
void BankFunction::processLogin(QNetworkReply* reply)
{
    loginToken.clear();
    loginToken = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(loginToken);
    int isLocked = jsonResponse["isLocked"].toInt();

    qDebug() << loginToken;

    int test = QString::compare(loginToken, "false");

    bool loginSuccessful = false;

    if (loginToken.length() == 0) //No reply from server
    {
        emit loginResult(2);
    }
    else
    {
        if (loginToken.contains("-4078")) //Error with database connection
        {
            emit loginResult(3);
        }
        else
        {
            if (test == 0)
            {
                emit loginResult(0);//Login failed. Emit signal to mainWindow
            }
            else
            {
                //emit loginResult(1);//Login successful. Emit signal to mainWindow

                if(isLocked == 1)
                {
                    emit loginResult(4);
                }
                else
                {
                    // Eli login onnistui ja haetaan sitten korttiin liitettyjen tilien lukumäärä:
                    loginSuccessful = true;
                }
            }
        }
    }
    networkAccessManager->deleteLater();
    reply->deleteLater();
    if (loginSuccessful)
    {
        getNumberOfAccounts();
    }
}

void BankFunction::getNumberOfAccounts()
{
    networkAccessManager = new QNetworkAccessManager(this);

    QString site_url = DatabaseURL::getBaseURL() + "/card/info/" + QString::number(cardId);
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), "bearer " + (loginToken));

    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(numAccountSlot(QNetworkReply*)));
    reply = networkAccessManager->get(request);
}


void BankFunction::withdrawMoney()
{
    networkAccessManager = new QNetworkAccessManager(this);

    QJsonObject jsonObj;
    jsonObj.insert("id", accountId);
    jsonObj.insert("amount", moneyAmount);

    QString site_url = DatabaseURL::getBaseURL() + "/account/withdraw";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), "bearer " + (loginToken));

    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processWithdrawal(QNetworkReply*)));
    reply = networkAccessManager->post(request, QJsonDocument(jsonObj).toJson());
}

void BankFunction::processWithdrawal(QNetworkReply* reply)
{
    responseData = reply->readAll();
    QJsonDocument jsonResponseData = QJsonDocument::fromJson(responseData);

    bool success = jsonResponseData[0]["success"].toInt(); // success = 1 if transaction was made and 0 if it failed
    balance = jsonResponseData[0]["balance"].toDouble();
    creditLimit = jsonResponseData[0]["credit_limit"].toInt();

    if (responseData.length() == 0)
    {
        qDebug() << "Server not responding";
        emit withdrawalResult(2);
    }
    else
    {
        if (responseData.contains("-4078"))
        {
            qDebug() << "Error in database connection";
            emit withdrawalResult(3);
        }
        else
        {
            if (success == 1)
            {
                emit withdrawalResult(1, balance);
            }
            else
            {
                emit withdrawalResult(0, balance);
            }
        }
    }
    networkAccessManager->deleteLater();
    reply->deleteLater();
}

void BankFunction::depositMoney()
{
    networkAccessManager = new QNetworkAccessManager(this);
    QJsonObject jsonObj;
    jsonObj.insert("id", accountId);
    jsonObj.insert("amount", moneyAmount);

    QString site_url = DatabaseURL::getBaseURL() + "/account/deposit";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), "bearer " + (loginToken));
    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processDeposit(QNetworkReply*)));
    reply = networkAccessManager->post(request, QJsonDocument(jsonObj).toJson());
}

void BankFunction::processDeposit(QNetworkReply* reply)
{
    responseData = reply->readAll();
    int test = QString::compare(responseData, "false");

    if (responseData.length() == 0)
    {
        qDebug() << "Server not responding";
        emit depositResult(2);
    }
    else
    {
        if (responseData.contains("-4078"))
        {
            qDebug() << "Error in database connection";
            emit depositResult(3);
        }
        else
        {
            if (test == 0)
            {
                qDebug() << "Sorry. You have insufficient funds to complete this transaction.";
                emit depositResult(0);
            }
            else
            {
                qDebug() << "Your transaction is complete. Your remaining balance is X €. Please take your cash and receipt.";
                emit depositResult(1);
            }
        }
    }
}

void BankFunction::makeDonation()
{
    networkAccessManager = new QNetworkAccessManager(this);
    QJsonObject jsonObj;
    int temp = moneyAmount;
    jsonObj.insert("id", accountId);
    jsonObj.insert("amount", temp);

    QString site_url = DatabaseURL::getBaseURL() + "/account/donation";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), "bearer " + (loginToken));
    
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processDonation(QNetworkReply*)));
    reply = networkAccessManager->post(request, QJsonDocument(jsonObj).toJson());
}

void BankFunction::processCustomer(QNetworkReply* reply)
{
    customerName = reply->readAll();


    networkAccessManager->deleteLater();
    reply->deleteLater();
}

void BankFunction::requestTransactions()
{
    networkAccessManager = new QNetworkAccessManager(this);
    //Set the URL based on the currently accessed account
    QString site_url = DatabaseURL::getBaseURL() + "/transactions/account/" + QString::number(accountId);
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), "bearer " + (loginToken));
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processTransactions()));
    reply = networkAccessManager->get(request);

}

void BankFunction::requestCustomer()
{
    networkAccessManager = new QNetworkAccessManager(this);
    QString site_url = DatabaseURL::getBaseURL() + "/customer/"+QString::number(customerId);
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"), "bearer " + (loginToken));
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processTransactions()));
    reply = networkAccessManager->get(request);
}

QVector<TransactionData*> BankFunction::GetTransactions()
{
    return transactions;
}

void BankFunction::logOut()
{
    loginToken.clear();
}

double BankFunction::getBalance()
{
    return balance;
}

int BankFunction::getCreditLimit()
{
    return creditLimit;
}

QString BankFunction::getCustomerName()
{
    return customerName;
}

void BankFunction::processTransactions()
{
    QString strReply = (QString)reply->readAll();
    qDebug() << strReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

    QJsonArray jsonArray = jsonResponse.array();

    for (int x = transactions.size()-1; x >= 0; x--)
    {
        delete transactions.at(x);
    }
    transactions.clear();
    for (int i = jsonArray.size()-1; i >= 0; i--)
    {
        QJsonObject jsonObj = jsonArray.at(i).toObject();

        TransactionData* trData = new TransactionData();

        trData->transactionID = QString::number(jsonObj["id_transaction"].toInt());
        trData->accountID = jsonObj["id_account"].toInt();
        //trData->dateTime = jsonObj["date"].toString();

        QDateTime dateTime = QDateTime::fromString(jsonObj["date"].toString(), "yyyy-MM-ddThh:mm:ss.zzzZ");
        QString newStr = dateTime.toString("dd.MM.yyyy");
        trData->dateTime = newStr;

        trData->eventType = jsonObj["event"].toString();
        trData->amount = QString::number(jsonObj["amount"].toDouble());
        transactions.push_back(trData);
    }
    emit transactionsResult(1);//Tell usermenu or transactions UI that the transactions list is ready to be filled with data.

    networkAccessManager->deleteLater();
    reply->deleteLater();    
}

void BankFunction::processDonation(QNetworkReply* reply)
{
    
    responseData = reply->readAll();
    qDebug() << responseData;
    QJsonDocument jsonResponseData = QJsonDocument::fromJson(responseData);
    int test = QString::compare(responseData, "false");
    if (responseData.contains("Unauthorized"))
    {
        qDebug() << "Unauthorized request";
    }

    if (responseData.length() == 0)
    {
        qDebug() << "Server not responding";
        emit donationResult(2);
    }
    else
    {
        if (responseData.contains("-4078"))
        {
            qDebug() << "Error in database connection";
            emit donationResult(3);
        }
        else
        {
            if (test == 0)
            {
                qDebug() << "Error! Donation failed!.";
                emit donationResult(0);
            }
            else
            {
                qDebug() << "Donation completed successfully.";
                emit donationResult(1);
            }
        }
    }
}

void BankFunction::setAccountId(int accountId)
{
    this->accountId = accountId;
}

void BankFunction::setMoneyAmount(int moneyAmount)
{
    this->moneyAmount = moneyAmount;
}

void BankFunction::getAccountInfo()
{
    networkAccessManager = new QNetworkAccessManager(this);
    QString site_url = DatabaseURL::getBaseURL() + "/account/getinfo/" + QString::number(cardId) + "/" + QString::number(accountType);
    QNetworkRequest request((site_url));

    request.setRawHeader(QByteArray("Authorization"), "bearer " + (loginToken));

    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processAccountInfo(QNetworkReply*)));
    reply = networkAccessManager->get(request);
}

void BankFunction::processAccountInfo(QNetworkReply* reply)
{
    qDebug() << reply;
    responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

    // Saadaan käyttäjän nimet, saldo ja credit limitti
    customerName = jsonResponse["name"].toString();
    balance = jsonResponse["balance"].toDouble();
    creditLimit = jsonResponse["credit_limit"].toInt();
    accountId = jsonResponse["id_account"].toInt();
    //setAccountId(accountId);
    qDebug() << "Testi:" + customerName + " Balance:" + QString::number(balance) + " Credit limit:" + QString::number(creditLimit) + " Account ID:" + QString::number(accountId);
    emit setCustomerName(customerName);
    networkAccessManager->deleteLater();
    reply->deleteLater();
}

void BankFunction::setAccountType(int type)
{
    accountType = type;
    getAccountInfo();
}

void BankFunction::numAccountSlot(QNetworkReply* reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);

    int numberOfAccounts = jsonResponse[0]["number_of_accounts"].toInt();
    qDebug() << "Number of accounts:" << numberOfAccounts;

    reply->deleteLater();
    networkAccessManager->deleteLater();

    // Korttiin liitettyjen tilien lukumäärä selvillä ja osataan päättää mihin näkymään siirrytään..

    if (numberOfAccounts == 1) // If user has only one account associated with their card, it means they have only debit account and we can skip chooseAccount window
    {        
        accountType = 0;
        getAccountInfo();
        emit loginResult(5);
    }
    else
    {
        emit loginResult(1);
    }
}
