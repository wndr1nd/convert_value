#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     setFixedSize(513,300);

     ui->From->setText("From");
     ui->To->setText("To");

     ui->From->setReadOnly(true);
     ui->To->setReadOnly(true);

    ui->convertButton->setText("Convert");

     QStringList currencies;

     currencies.push_back("EUR");
     currencies.push_back("USD");
     currencies.push_back("BYN");
     currencies.push_back("KZT");
     currencies.push_back("BRL");
     currencies.push_back("RUB");
     currencies.push_back("UAH");
     currencies.push_back("INR");
     currencies.push_back("QAR");
     currencies.push_back("PLN");
     currencies.push_back("CZK");

     ui->currFrom->insertItems(0, currencies);
     ui->currTo->insertItems(0, currencies);

     manager = new QNetworkAccessManager(this);
     connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}


 void MainWindow::on_convertButton_clicked()
 {
     if (ui->Input->text() != "")
           {

             ui->convertButton->setEnabled(false);

           }
     else
     {
         QMessageBox::warning(this, "Alert", "Need value");
     }

     QString url = "https://www.cbr-xml-daily.ru/daily_json.js";

     QNetworkRequest request= QNetworkRequest(QUrl(url));
     manager->get(request);

}


 void MainWindow::finished(QNetworkReply* reply)
 {
     QByteArray response = reply->readAll();
     QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
     QJsonObject jsonObj = jsonResponse.object();

     auto new_json = jsonObj["Valute"];

     auto tmp = new_json[ui->currFrom->currentText()];

     double cf = 1;

     cf = tmp["Value"].toDouble();

     if (cf == 0)
         {
             cf = 1;
         }

     if (ui->currTo->currentText() != "RUB")
     {
         tmp = new_json[ui->currTo->currentText()];
         cf /= tmp["Value"].toDouble();
     }


     double amount = ui->Input->text().toDouble();

     double result = amount * cf;
     ui->Output->setText(QString::number(result));
     ui->convertButton->setEnabled(true);

 }
