#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMainWindow>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_convertButton_clicked();
    void finished(QNetworkReply* reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager;
};
#endif // MAINWINDOW_H
