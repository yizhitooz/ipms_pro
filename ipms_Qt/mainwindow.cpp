#include "mainwindow.h"
#include "RechargeWidget.h"
#include "chargerulewidget.h"
#include "managewidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // initDatabase();
    initInformationTableView();
    initGarageTableView();
    initParkingNum();
    setPrice();

    QDate current_date = QDate::currentDate();
    ui->dateEdit->setDate(current_date);
    // timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &MainWindow::showParkingNum);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    // 设置请求的URL
    request.setUrl(QUrl("http://localhost:8080/parking/lot/search/all"));

    // 发送POST请求，并将JSON数据发送到服务器
    QNetworkReply *reply = manager->get(request);

    // 连接网络请求的完成信号
    connect(reply, &QNetworkReply::finished, [=]() {
        onNetworkReplyFinishedOnMainWindowLoad(reply);
        manager->deleteLater(); // 删除 manager
    });
}

MainWindow::~MainWindow() { delete ui; }

#if !_USE_SPRINGBOOT
void MainWindow::initDatabase() {
    database = new QSqlDatabase;
#if _USE_MYSQL
    *database = QSqlDatabase::addDatabase("QMYSQL");
    // 数据库IP
    database->setHostName("127.0.0.1");
    // 数据库端口
    database->setPort(3306);
    // 数据库名
    database->setDatabaseName("ipms");
    // 数据库用户名
    database->setUserName("root");
    // 数据库密码
    database->setPassword("123456");
#elif _USE_SQLITE /* _USE_MYSQL */
    *database = QSqlDatabase::addDatabase("QSQLITE");
    database->setUserName("uzalwong.local");
    database->setPassword("@Dg281764");
    // database->setPort(0);
    database->setHostName("raspberrypi.local");
    QString databaseFilePath =
            QDir::homePath() + "/Code/IMPS_Pro/Car_recognition/ipms.db";
    database->setDatabaseName(databaseFilePath);
    // database->setDatabaseName("/home/uzalwong/Code/IMPS_Pro/Car_recognition/ipms.db");
#endif                        /* _USE_SQLITE */
    // 开启数据库
    if (!database->open()) {
        qDebug() << "Error: Failed to open database:"
                         << database->lastError().text();
    } else {
        qDebug() << "Database opened successfully.";
    }
}
#endif /* !_USE_SPRINGBOOT */

void MainWindow::initInformationTableView() {
    information_table_model = new QSqlTableModel;
    information_table_model->setTable("parkinginformation");
    information_table_model->setHeaderData(1, Qt::Horizontal, "车牌号");
    information_table_model->setHeaderData(2, Qt::Horizontal, "入场时间");
    information_table_model->setHeaderData(3, Qt::Horizontal, "出场时间");
    information_table_model->setHeaderData(4, Qt::Horizontal, "费用(元)");
    information_table_model->setHeaderData(5, Qt::Horizontal, "已完成");
    information_table_model->setHeaderData(6, Qt::Horizontal, "入场口");
    information_table_model->setHeaderData(7, Qt::Horizontal, "出场口");
    ui->informationTableView->setModel(information_table_model);

    ui->informationTableView->hideColumn(0);
}

void MainWindow::initGarageTableView() {
    garage_table_model = new QSqlTableModel;
    garage_table_model->setTable("parkinginformation");
    garage_table_model->setHeaderData(1, Qt::Horizontal, "车牌号");
    garage_table_model->setHeaderData(2, Qt::Horizontal, "入场时间");
    garage_table_model->setHeaderData(6, Qt::Horizontal, "入场口");
    ui->garageTableView->setModel(garage_table_model);

    ui->garageTableView->hideColumn(0);
    ui->garageTableView->hideColumn(3);
    ui->garageTableView->hideColumn(4);
    ui->garageTableView->hideColumn(5);
    ui->garageTableView->hideColumn(7);
}

void MainWindow::initLevel() {
    switch (level) {
    case 0:
        ui->chargeRulePageButton->setEnabled(false);
    case 1:
        ui->managePageButton->setEnabled(false);
    case 2:
    default:
        break;
    }
}

void MainWindow::initParkingNum() {
#if _USE_SPRINGBOOT
#else
    QSqlQuery query;
    QString str = QString("select * from systemdata");
    query.exec(str);
    if (query.next()) {
        max_num = query.value(2).toInt();
    }
    if (query.next()) {
        current_num = query.value(2).toInt();
    }
#endif
}

bool MainWindow::getVehicleIDAndPlace(QString &id, QString &place) {
    id = ui->vehicleIDLineEdit->text();
    place = ui->ParkingLotComboBox->currentText();
    if (id.isEmpty() || place.isEmpty())
        return false;
    return true;
}

void MainWindow::level_rec_from_login(int level) {
    this->level = level;
    initLevel();
}

void MainWindow::unlogin() {
    this->close();
    // timer->start(TIMEOUT);
}

double MainWindow::calculate_money(QDateTime &inTime, QDateTime &outTime,
                                                                     double &price) {
    double time = inTime.secsTo(outTime) / (60 * 60);
    double money = time * price;
    return money;
}

int MainWindow::how_to_get_money(QDateTime &packageDay, QDateTime &inTime,
                                                                 QDateTime &outTime) {
    qint64 out_over = packageDay.secsTo(outTime);
    qint64 in_over = packageDay.secsTo(inTime);
    // 出库时未到期
    if (out_over < 0)
        return 1;
    // 入库时未到期但出库时到期
    if (in_over < 0)
        return 2;
    return 0;
}

void MainWindow::setPrice() {
    QSqlQuery query;
    QString str =
            QString("select * from chargingmethod where chargingMethod = 'hourly'");
    query.exec(str);
    if (query.next()) {
        price = query.value(2).toDouble();
    }
}

bool MainWindow::enableIn() {
#if _USE_SPRINGBOOT

#elif
    QSqlQuery query;
    QString str =
        QString("select * from systemdata where dataname = 'currentspace'");
    query.exec(str);
    if (query.next()) {
        current_num = query.value(2).toInt();
    }
    return max_num > current_num ? true : false;
#endif
}

bool MainWindow::addCurrentNum() {
    if (current_num < max_num) {
        current_num++;
        QSqlQuery query;
        QString str = QString("update systemdata set datavalue = datavalue + 1 "
                                                    "where dataname = 'currentspace'");
        query.exec(str);
        str = QString("select * from systemdata where dataname = 'currentspace'");
        query.exec(str);
        if (query.next()) {
            current_num = query.value(2).toInt();
        }
        return true;
    }
    return false;
}

bool MainWindow::reduceCurrentNum() {
    if (current_num > 0) {
        QSqlQuery query;
        QString str = QString("update systemdata set datavalue = datavalue - 1 "
                                                    "where dataname = 'currentspace'");
        query.exec(str);
        str = QString("select * from systemdata where dataname = 'currentspace'");
        query.exec(str);
        if (query.next()) {
            current_num = query.value(2).toInt();
        }
        return true;
    }
    return false;
}

void MainWindow::showInfo(const QString &vehicleId, const QString &place,
                                                    double bill, QDateTime &time, int flag) {
    QString str = QString("时间:%1\n车辆:%2\n检查口:%3\n")
                                        .arg(time.toString("yyyy-MM-dd hh:mm:ss"))
                                        .arg(vehicleId)
                                        .arg(place);
    if (flag == 1) {
        str += QString("费用:%1\n车辆离场").arg(bill);
    }
    if (flag == 2) {
        str += QString("车辆入场");
    }
    ui->billLabel->setText(str);
}

void MainWindow::inAndOutClean() {
    ui->vehicleIDLineEdit->clear();
    ui->ParkingLotComboBox->currentText();
}

void MainWindow::showParkingNum() {
    QJsonObject data = ui->ParkingLotComboBox->currentData().toJsonObject();
    qDebug()<<"设置label中"<<data;
    QString str = QString(
            "最大停车数: " + QString::number(data["maxCarPark"].toInt()) +
            "\n当前停车数: " + QString::number(data["currentCarPark"].toInt()));
    ui->spaceLabel->setText(str);
}

// 页面跳转相关
/**********************************/
void MainWindow::on_inAndOutPageButton_clicked() {
        ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_garagePageButton_clicked() {
        ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_queryPageButton_clicked() {
        ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_rechargePageButton_clicked() {
        RechargeWidget *recharge_widget = new RechargeWidget;
        recharge_widget->show();
}

void MainWindow::on_chargeRulePageButton_clicked() {
        ChargeRuleWidget *charge_rule_widget = new ChargeRuleWidget;
        charge_rule_widget->show();
        connect(charge_rule_widget, &ChargeRuleWidget::money_change, [=] {
                setPrice();
        //                qDebug() << price;
        });
}

void MainWindow::on_managePageButton_clicked() {
        ManageWidget *manage_widget = new ManageWidget;
        manage_widget->show();
}
/**********************************/

// 入库
/**********************************/
void MainWindow::on_inButton_clicked() {
#if _USE_SPRINGBOOT

#else
        if (!enableIn()) {
                QMessageBox::information(this, "警告", "当前已无空闲车位");
        return;
    }
        // 占位
        addCurrentNum();
#endif
        QString vehicleId;
        QString place;
        QDateTime current_time = QDateTime::currentDateTime();
        // 输入为空判断
        if (!getVehicleIDAndPlace(vehicleId, place)) {
                QMessageBox::information(this, "警告", "请输入车牌和检查口");
                reduceCurrentNum();
                return;
        }
#if _USE_SPRINGBOOT
        // 创建对象并设置属性
        QJsonObject jsonObject;
        jsonObject["plate"] = vehicleId;
        jsonObject["password"] = place;

        // 将对象转换为JSON格式的数据
        QJsonDocument jsonDocument(jsonObject);
        QByteArray jsonData = jsonDocument.toJson();

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkRequest request;

        // 设置请求的URL
        request.setUrl(QUrl("http://localhost:8080/parking/record/enter"));

        // 设置请求头
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // 发送POST请求，并将JSON数据发送到服务器
        reply = manager->post(request, jsonData);

        // 连接网络请求的完成信号
        connect(reply, &QNetworkReply::finished, [=]() {
            onNetworkReplyOnEnter(reply);
            manager->deleteLater(); // 删除 manager
        });
#elif
        QSqlQuery query;

        // 检测该车是否登记
        QString str = QString("select * from vehicle "
                                                     "where vehicleID = '%1'")
                                                    .arg(vehicleId);

        query.exec(str);
        // 未登记则进行登记
        if (!query.next()) {
                str = QString("insert into vehicle "
                                    "(vehicleID) "
                                    "values('%1')")
                            .arg(vehicleId);

        query.exec(str);
    }
        // 检测该车是否已在库中
        str = QString("select * from parkinginformation "
                                "where vehicleID = '%1'and isfinish = 'no'")
                        .arg(vehicleId);

        query.exec(str);
        if (!query.next()) {
                str = QString("insert into parkinginformation "
                                    "(vehicleID,inTime,isfinish,entrance) "
                                    "values('%1','%2','no',%3)")
                            .arg(vehicleId)
                            .arg(current_time.toString("yyyy-MM-dd hh:mm:ss"))
                            .arg(place);
        query.exec(str);
        inAndOutClean();
        showInfo(vehicleId, place, 0, current_time, 2);
    } else {
        QMessageBox::information(this, "警告", "该车已在库中");
        reduceCurrentNum();
        return;
    }
#endif
}
/**********************************/

// 出库与计费
/**********************************/
void MainWindow::on_outButton_clicked() {
    QString vehicleId;
    QString place;
    double bill = 0;
    QDateTime current_time = QDateTime::currentDateTime();
    if (!getVehicleIDAndPlace(vehicleId, place)) {
        QMessageBox::information(this, "警告", "请输入车牌和检查口");
        return;
    }
    QSqlQuery query;
    // 检测该车是否登记
    QString str = QString("select * from vehicle "
                                                "where vehicleID = '%1'")
                                        .arg(vehicleId);
    query.exec(str);
    // 未登记则进行登记
    if (!query.next()) {
        str = QString("insert into vehicle (vehicleID) "
                                    "values('%1')")
                            .arg(vehicleId);
        query.exec(str);
    }
    // 检测该车是否已在库中
    str = QString("select * from parkinginformation "
                                "where vehicleID = '%1' and isfinish = 'no'")
                        .arg(vehicleId);

    query.exec(str);
    if (!query.next()) {
        QMessageBox::information(this, "警告", "该车未在库中");
        return;
    } else {
        QDateTime in_time = query.value(2).toDateTime();
        QDateTime out_time = current_time;
        QDateTime package_day;

        // 计费
        str =
                QString("select * from vehicle where vehicleID = '%1'").arg(vehicleId);
        query.exec(str);
        if (query.next()) {
            package_day = query.value(2).toDateTime();
        }

        int mode = 0;
        if (package_day.isNull()) {
            mode = 0;
        } else {
            mode = how_to_get_money(package_day, in_time, out_time);
        }

        if (mode == 0) {
            bill = calculate_money(in_time, out_time, price);
        }
        if (mode == 1) {
            bill = 0;
        }
        if (mode == 2) {
            bill = calculate_money(package_day, out_time, price);
        }
        // 写入
        str = QString(
                            "update parkinginformation "
                            "set outTime = '%1', bill = %2, isfinish = 'yes', exitgoal = %3 "
                            "where vehicleID = '%4' and isfinish = 'no'")
                            .arg(current_time.toString("yyyy-MM-dd hh:mm:ss"))
                            .arg(bill)
                            .arg(place)
                            .arg(vehicleId);
        query.exec(str);

        reduceCurrentNum();
        inAndOutClean();
        showInfo(vehicleId, place, bill, current_time, 1);
    }
}
/**********************************/

void MainWindow::on_informationSearchButton_clicked() {
    QString vehicleId = ui->informationVehicleIDLineEdit->text();
    QDate date = ui->dateEdit->date();

    QString str;
    if (!vehicleId.isEmpty()) {
        str += QString("(vehicleID like '%1%') and ").arg(vehicleId);
    }

    str += QString("(inTime like '%1%')").arg(date.toString("yyyy-MM-dd"));
    information_table_model->setFilter(str);
    information_table_model->select();
}

void MainWindow::on_refreshButton_clicked() {
    QString filter_str = QString("(isfinish = 'no')");
    garage_table_model->setFilter(filter_str);
    garage_table_model->select();
}

void MainWindow::on_AllInformatioButton_clicked() {
    information_table_model->setFilter("");
    information_table_model->select();
}

void MainWindow::on_ParkingLotComboBox_currentIndexChanged(int index) {
    showParkingNum();
}

void MainWindow::onNetworkReplyFinishedOnMainWindowLoad(QNetworkReply *reply) {
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
            QJsonArray dataArray = jsonObj["data"].toArray();
            // 遍历数组中的每个对象
            for (const QJsonValue &value : dataArray) {
                QJsonObject obj = value.toObject();
                ui->ParkingLotComboBox->addItem(obj["name"].toString(),QVariant::fromValue(obj));
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

    showParkingNum();
}

void MainWindow::on_pushButtonCheck_clicked()
{
    ui->ParkingLotComboBox->clear();
    QJsonObject qJsonObj = ui->ParkingLotComboBox->currentData().toJsonObject();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    // 设置请求的URL
    request.setUrl(QUrl("http://localhost:8080/parking/lot/search/all"));

    // 发送POST请求
    QNetworkReply *reply = manager->get(request);

    // 连接网络请求的完成信号
    connect(reply, &QNetworkReply::finished, [=]() {
        onNetworkReplyFinishedOnMainWindowLoad(reply);
        manager->deleteLater(); // 删除 manager
    });
}

void MainWindow::onNetworkReplyOnEnter(QNetworkReply *reply){
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

