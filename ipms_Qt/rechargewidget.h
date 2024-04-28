#ifndef RECHARGEWIDGET_H
#define RECHARGEWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

#define _USE_SPRINGBOOT 1

namespace Ui {
class RechargeWidget;
}

class RechargeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RechargeWidget(QWidget *parent = nullptr);
    void onNetworkReplyFinished(QNetworkReply *reply);
    ~RechargeWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RechargeWidget *ui;
    QNetworkReply *reply;
};

#endif // RECHARGEWIDGET_H
