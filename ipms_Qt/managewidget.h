#ifndef MANAGEWIDGET_H
#define MANAGEWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#define _USE_SPRINGBOOT 1

namespace Ui {
class ManageWidget;
}

class ManageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManageWidget(QWidget *parent = nullptr);
    ~ManageWidget();
    void setComBox();
    void extracted(QJsonArray &dataArray);
    void onNetworkReplyFinishedWidgetOnload(QNetworkReply *reply);
    void onNetworkReplyFinishedOnInfo(QNetworkReply *reply);
    void onNetworkReplyFinishedOnChange(QNetworkReply *reply);

private slots:
    void setInformationLabel(const QString &text);
    void on_changeButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::ManageWidget *ui;
    QNetworkReply *reply;
    QJsonArray *dataArray;
};

#endif // MANAGEWIDGET_H
