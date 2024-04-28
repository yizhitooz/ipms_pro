#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

    int getLevel();
    void closeEvent(QCloseEvent *event);
    friend void onNetworkReplyFinished(QNetworkReply *reply);
signals:
    void level_sent(int level);
    void unlogin_close_signals();

private slots:
    void unlogin_close();
    void on_loginButton_clicked();
    void onNetworkReplyFinished(QNetworkReply *reply);

private:
    Ui::LoginWidget *ui;
    QNetworkReply *reply;
    int level;
    bool islogin = false;
};

#endif // LOGINWIDGET_H
