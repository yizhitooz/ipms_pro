#include "rechargewidget.h"
#include "ui_rechargewidget.h"
#include <QJsonObject>

RechargeWidget::RechargeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RechargeWidget)
{
    ui->setupUi(this);
}

RechargeWidget::~RechargeWidget()
{
    delete ui;
}

void RechargeWidget::on_pushButton_clicked()
{
    QDateTime current_time = QDateTime::currentDateTime();
    int date;
    QString plate = ui->vehicleIDLineEdit->text();
    if(ui->monthlyRadioButton->isChecked())
    {
        date = 30;
    }
    else if(ui->quarterlyRadioButton->isChecked())
    {
        date = 90;
    }
    else if (ui->annualRadioButton->isChecked())
    {
        date = 365;
    }
    else
    {
        QMessageBox::warning(this,"警告","未选择套餐");
        return;
    }

#if _USE_SPRINGBOOT
    QJsonObject jsonObject;
    jsonObject["plate"] = plate;
    jsonObject["dueDate"] = current_time.addDays(date).toString("yyyy-MM-dd hh:mm:ss");

    // 将对象转换为JSON格式的数据
    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonData = jsonDocument.toJson();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    // 设置请求的URL
    request.setUrl(QUrl("http://localhost:8080/vehicle/charge"));

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
    QSqlQuery query;
    QDateTime time;
    //检查该车是否登记
    QString str = QString("select * from vehicle "
                          "where vehicleID = '%1'")
                      .arg(vehicleId);
    query.exec(str);
    //未登记则先登记
    if(!query.next())
    {
        str = QString("insert into vehicle (vehicleID) "
                      "values('%1')")
                  .arg(vehicleId);
        query.exec(str);
        str = QString("select * from vehicle "
                      "where vehicleID = '%1'")
                  .arg(vehicleId);
        query.exec(str);
        time = current_time.addDays(date);
        str = QString("update vehicle set packageDay = '%1'").arg(time.toString("yyyy-MM-dd hh:mm:ss"));
        query.exec(str);
        QMessageBox::information(this,"提示","充值成功");
    }
    else
    {
        QDateTime end_time;
        if(query.value(2).toString().isEmpty())
        {
            end_time = current_time;
        }
        else
        {
            end_time = query.value(2).toDateTime();
        }
        time = end_time.addDays(date);
        str = QString("update vehicle set packageDay = '%1' where vehicleID = '%2'").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(vehicleId);
        query.exec(str);
        QMessageBox::information(this,"提示","充值成功");
    }
#endif
}

void RechargeWidget::onNetworkReplyFinished(QNetworkReply *reply){
    // 检查请求是否成功
    if (reply->error() == QNetworkReply::NoError) {
        // 读取响应数据
        QByteArray responseData = reply->readAll();
        qDebug() << "Response:" << responseData;

        // 解析 JSON 数据
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Failed to parse JSON:" << parseError.errorString();
            return;
        }

        if (!jsonDoc.isObject()) {
            qDebug() << "JSON is not an object.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        // 检查响应中是否包含 code 字段，并且其值为 "200"
        if (jsonObj.contains("code") && jsonObj["code"].isString() && jsonObj["code"].toString() == "200") {
            // 检查响应中是否包含 data 字段
            if (jsonObj.contains("data") && jsonObj["data"].isObject()) {
                QJsonObject dataObj = jsonObj["data"].toObject();
                QMessageBox::information(this,"提示","充值成功");
                this->close();
            }
        } else {
            // 提取错误消息
            if (jsonObj.contains("msg") && jsonObj["msg"].isString()) {
                QString errorMsg = jsonObj["msg"].toString();
                QMessageBox::critical(this,"出现错误",errorMsg);
            }
        }
    } else {
        // 打印错误信息
        QMessageBox::information(this,"提示","请求方法有误");
    }

    // 释放资源
    reply->deleteLater();
}
