﻿#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "mainwindow.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    // 定义样式表

    QString styleSheet = "QLineEdit { background-color: white;"
                         "border-width: 5px; border-style: solid; border-color: gray;"
                         "border-radius: 10px; padding: 0px 10px; }"
                         "QLineEdit:hover { background-color: lightgray; color: black; }"
                         "QLineEdit:focus { background-color: lightblue; }";
    /*原输入框设计
    QLineEdit{
        border-width:5px;
        border-style:solid;
        border-color:gray;
        border-radius:10px;
        padding: 0px 10px;
    }
    */
    /*ancount输入框实现伪装态效果*/
    ui->accountLineEdit->setPlaceholderText("please enter your account"); // 设置提示文字

    ui->accountLineEdit->setStyleSheet(styleSheet);

    // 连接信号和槽
    connect(ui->accountLineEdit, &QLineEdit::textEdited, [=](const QString& text) {
        if (text.isEmpty()) {
            ui->accountLineEdit->setStyleSheet(styleSheet + "QLineEdit { color: gray; }");
        } else {
            ui->accountLineEdit->setStyleSheet(styleSheet + "QLineEdit { color: black; }");
        }
    });
    /*####################*/
    /*password输入框实现伪装态效果*/
    ui->passworkLineEdit->setPlaceholderText("please enter your password"); // 设置提示文字

    ui->passworkLineEdit->setStyleSheet(styleSheet);

    // 连接信号和槽
    connect(ui->passworkLineEdit, &QLineEdit::textEdited, [=](const QString& text) {
        if (text.isEmpty()) {
            ui->passworkLineEdit->setStyleSheet(styleSheet + "QLineEdit { color: gray; }");
        } else {
            ui->passworkLineEdit->setStyleSheet(styleSheet + "QLineEdit { color: black; }");
        }
    });
    /*####################*/
    connect(this,&QWidget::close,this,&LoginWidget::unlogin_close);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

int LoginWidget::getLevel()
{
    return level;
}

void LoginWidget::closeEvent(QCloseEvent *event)
{
    if(!islogin)
        emit unlogin_close_signals();
    event->accept();
}

void LoginWidget::unlogin_close()
{
    if(!islogin)
        emit unlogin_close_signals();
}

void LoginWidget::on_loginButton_clicked()
{
    QString account = ui->accountLineEdit->text();
    QString password = ui->passworkLineEdit->text();

    if(account.isEmpty())
    {
        QMessageBox::information(this,"提示","账号不能为空");
        return;
    }
    if(password.isEmpty())
    {
        QMessageBox::information(this,"提示","密码不能为空");
        return;
    }
#if _USE_SPRINGBOOT
    // 创建对象并设置属性
    QJsonObject jsonObject;
    jsonObject["account"] = account;
    jsonObject["password"] = password;

    // 将对象转换为JSON格式的数据
    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonData = jsonDocument.toJson();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    // 设置请求的URL
    request.setUrl(QUrl("http://localhost:8080/user/login/"));

    // 设置请求头
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送POST请求，并将JSON数据发送到服务器
    reply = manager->post(request, jsonData);

    // 连接网络请求的完成信号
    connect(reply, &QNetworkReply::finished, [=]() {
        onNetworkReplyFinished(reply);
        manager->deleteLater(); // 删除 manager
    });

#else
    QString sql = QString("select * from authority where account = '%1'").arg(account);
    QSqlQuery query(sql);
    if(query.next())
    {
        QString rec_password = query.value(3).toString();
        if(rec_password != password)
        {
            QMessageBox::information(this,"提示","账号或密码错误");
        }
        else {
            QMessageBox::information(this,"提示","登录成功");
            level = query.value(1).toInt();
            islogin = true;
            emit level_sent(level);
            this->close();
        }
    }
#endif
}

void LoginWidget::onNetworkReplyFinished(QNetworkReply *reply)
{
    // 检查请求是否成功
    if (reply->error() == QNetworkReply::NoError) {
        // 读取响应数据
        QByteArray responseData = reply->readAll();
        qDebug() << "Response:" << responseData;

        // 解析 JSON 数据
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            QMessageBox::information(this,"错误","Failed to parse JSON:"+parseError.errorString());
            return;
        }

        if (!jsonDoc.isObject()) {
            QMessageBox::information(this,"错误","JSON is not an object.");
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        // 检查响应中是否包含 code 字段，并且其值为 "200"
        if (jsonObj.contains("code") && jsonObj["code"].isString() && jsonObj["code"].toString() == "200") {
            // 检查响应中是否包含 data 字段
            if (jsonObj.contains("data") && jsonObj["data"].isObject()) {
                QJsonObject dataObj = jsonObj["data"].toObject();

                if (dataObj.contains("level") && dataObj["level"].isDouble()) {
                    level = dataObj["level"].toInt();
                }

                islogin = true;
                emit level_sent(level);
                this->close();
            }
        } else {
            // 提取错误消息
            if (jsonObj.contains("msg") && jsonObj["msg"].isString()) {
                QString errorMsg = jsonObj["msg"].toString();
                QMessageBox::information(this,"错误","Error message:" + errorMsg);
            }
        }
    } else {
        // 打印错误信息
        QMessageBox::information(this,"提示","账号或密码错误");
    }

    // 释放资源
    reply->deleteLater();
}

