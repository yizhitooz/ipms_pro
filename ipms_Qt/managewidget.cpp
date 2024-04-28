#include "managewidget.h"
#include "ui_managewidget.h"

ManageWidget::ManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageWidget)
{
    ui->setupUi(this);
    ui->levelComboBox->addItem("0");
    ui->levelComboBox->addItem("1");
    ui->levelComboBox->addItem("2");
    ui->levelComboBox->addItem("3");
    setComBox();
    void(QComboBox::*p)(const QString &text) = &QComboBox::activated;
    void(ManageWidget::*q)(const QString &text) = &ManageWidget::setInformationLabel;
    connect(ui->peopleComboBox,p,this,q);
}

ManageWidget::~ManageWidget()
{
    delete ui;
}

void ManageWidget::setComBox()
{
#if _USE_SPRINGBOOT
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    // 设置请求的URL
    request.setUrl(QUrl("http://localhost:8080/user/search/manager"));

    reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        onNetworkReplyFinishedWidgetOnload(reply);
        manager->deleteLater(); // 删除 manager
    });
#else
    QSqlQuery query;
    QString str = QString("select * from authority where level < 2");
    query.exec(str);
    while (query.next())
    {
        ui->peopleComboBox->addItem(query.value(0).toString());
    }
#endif
}

void ManageWidget::setInformationLabel(const QString &text)
{
    if(text == QString("请选择人员"))
        return;
#if _USE_SPRINGBOOT
    // 创建对象并设置属性
    QJsonObject jsonObject;
    jsonObject["account"] = text;

    // 将对象转换为JSON格式的数据
    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonData = jsonDocument.toJson();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    // 设置请求的URL
    request.setUrl(QUrl("http://localhost:8080/user/search/account/"+text));

    // 发送POST请求，并将JSON数据发送到服务器
    reply = manager->get(request);

    // 连接网络请求的完成信号
    connect(reply, &QNetworkReply::finished, [=]() {
        onNetworkReplyFinishedOnInfo(reply);
        manager->deleteLater(); // 删除 manager
    });

#else
    QSqlQuery query;
    QString str = QString("select * from authority where managerID = %1").arg(text.toInt());
    query.exec(str);
    while (query.next())
    {
        QString label_text = QString("managerID:%1,level:%2").arg(query.value(0).toString()).arg(query.value(1).toString());
        ui->informationLabel->setText(label_text);
    }
#endif
}

void ManageWidget::on_changeButton_clicked()
{
    QString select_level = ui->levelComboBox->currentText();
    int level;
    if(select_level == QString("权限等级"))
    {
        return;
    }else{
        level = select_level.toInt();
    }
    QString people = ui->peopleComboBox->currentText();
    if(people == QString("请选择人员"))
    {
        return;
    }
#if _USE_SPRINGBOOT
    // 创建对象并设置属性
    QJsonObject jsonObject;
    jsonObject["account"] = people;
    jsonObject["level"] = level;

    // 将对象转换为JSON格式的数据
    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonData = jsonDocument.toJson();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    // 设置请求的URL
    request.setUrl(QUrl("http://localhost:8080/user/change"));

    // 设置请求头
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送POST请求，并将JSON数据发送到服务器
    reply = manager->post(request,jsonData);

    // 连接网络请求的完成信号
    connect(reply, &QNetworkReply::finished, [=]() {
        onNetworkReplyFinishedOnChange(reply);
        manager->deleteLater(); // 删除 manager
    });
#else
    QSqlQuery query;
    QString str = QString("update authority set level = %1 where managerID = %2").arg(select_level.toInt()).arg(people.toInt());
    if(query.exec(str))
    {
        QMessageBox::information(this,"提示","修改成功");
    }
#endif
}

void ManageWidget::extracted(QJsonArray &dataArray) {
    for (const QJsonValue &value : dataArray) {
        if (value.isObject()) {
            QJsonObject userObj = value.toObject();
            QString account = userObj["account"].toString();
            QString userName = userObj["userName"].toString();
            ui->peopleComboBox->addItem("account" + account +
                                        ",userName:" + userName);
        }
    }
}

void ManageWidget::onNetworkReplyFinishedWidgetOnload(QNetworkReply *reply) {
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
        if (jsonObj.contains("code") && jsonObj["code"].isString() &&
            jsonObj["code"].toString() == "200") {
            // 检查响应中是否包含 data 字段
            if (jsonObj.contains("data") && jsonObj["data"].isArray()) {
                QJsonArray dataArray = jsonObj["data"].toArray();
                // 遍历数组中的每个对象
                for (const QJsonValue &value : dataArray) {
                    QJsonObject obj = value.toObject();
                    ui->peopleComboBox->addItem(obj["account"].toString(), QVariant::fromValue(obj));
                }
            }
        } else {
            // 提取错误消息
            if (jsonObj.contains("msg") && jsonObj["msg"].isString()) {
                QString errorMsg = jsonObj["msg"].toString();
                QMessageBox::critical(this, "出现错误", errorMsg);
            }
        }
    } else {
        // 打印错误信息
        QMessageBox::information(this, "提示", "请求方法有误");
    }

    // 释放资源
    reply->deleteLater();
}

void ManageWidget::on_pushButton_clicked()
{
    ui->peopleComboBox->clear();
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    // 设置请求的URL
    request.setUrl(QUrl("http://localhost:8080/user/search/manager"));

    reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        onNetworkReplyFinishedWidgetOnload(reply);
        manager->deleteLater(); // 删除 manager
    });
}

void ManageWidget::onNetworkReplyFinishedOnInfo(QNetworkReply *reply){
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
        if (jsonObj.contains("code") && jsonObj["code"].isString() &&
            jsonObj["code"].toString() == "200") {
            // 检查响应中是否包含 data 字段
            QJsonObject dataObj = jsonObj["data"].toObject();

            QString info = QString("account:"+dataObj["account"].toString()+
                                   ",\nlevel:"+QString::number(dataObj["level"].toInt()));
            ui->informationLabel->setText(info);
        } else {
            // 提取错误消息
            if (jsonObj.contains("msg") && jsonObj["msg"].isString()) {
                QString errorMsg = jsonObj["msg"].toString();
                QMessageBox::critical(this, "出现错误", errorMsg);
            }
        }
    } else {
        // 打印错误信息
        QMessageBox::information(this, "提示", "请求方法有误");
    }

    // 释放资源
    reply->deleteLater();
}

void ManageWidget::onNetworkReplyFinishedOnChange(QNetworkReply *reply){
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
        if (jsonObj.contains("code") && jsonObj["code"].isString() &&
            jsonObj["code"].toString() == "200") {
            // 检查响应中是否包含 data 字段
            QJsonObject dataObj = jsonObj["data"].toObject();

            QString info = QString("account:"+dataObj["account"].toString()+
                                   ",\nlevel:"+QString::number(dataObj["level"].toInt()));
            ui->informationLabel->setText(info);
        } else {
            // 提取错误消息
            if (jsonObj.contains("msg") && jsonObj["msg"].isString()) {
                QString errorMsg = jsonObj["msg"].toString();
                QMessageBox::critical(this, "出现错误", errorMsg);
            }
        }
    } else {
        // 打印错误信息
        QMessageBox::information(this, "提示", "请求方法有误");
    }

    // 释放资源
    reply->deleteLater();
}

