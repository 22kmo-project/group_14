#include "charity.h"
#include "ui_charity.h"

charity::charity(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::charity)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->button_confirm, &QPushButton::clicked, this, &charity::donation);
    connect(ui->button_cancel, &QPushButton::clicked, this, &charity::button_cancel);
    connect(ui->buttonBack2, &QPushButton::clicked, this, &charity::button_cancel);
    connect(ui->buttonBack3, &QPushButton::clicked, this, &charity::button_cancel);
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
    selectedAmount = (ui->lineEdit_chooseamount->text()).toInt();
    emit setAmount(selectedAmount);
    emit makeDonation();
}

void charity::donationSlot(int result)

{
    switch (result)
    {
    case 0:
        qDebug() << "Virhe. Tilisi kate ei riitä.";
        ui->label_2->setText("Virhe. Tilisi kate ei riitä.\n\n");
        ui->stackedWidget->setCurrentIndex(2);
        break;
    case 1:
        qDebug() << "Lahjoitus suoritettu.";
        ui->label->setText("Lahjoitus suoritettu. \n\n Kiitos kun tuit järjestön\n" + charityName + "\ntärkeää työtä!");
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case 2:
        qDebug() << "Server not responding";
        break;
    case 3:
        qDebug() << "Error in database connection";
        break;
    }
}

void charity::button_cancel()
{
    emit changeWidget(2);
    ui->stackedWidget->setCurrentIndex(0); // resets donation windows stacked widget index after returning from "thank you" screen
    ui->lineEdit_chooseamount->clear(); // and also clears input field
}

void charity::on_button_kohde1_clicked()
{
    emit resetTime();
    charityName = "WWF";
}

void charity::on_button_kohde2_clicked()
{
    emit resetTime();
    charityName = "Unicef";
}

void charity::on_button_kohde3_clicked()
{
    emit resetTime();
    charityName = "Suomen Mielenterveys Ry";
}
