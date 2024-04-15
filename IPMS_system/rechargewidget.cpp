#include "rechargewidget.h"
#include "ui_rechargewidget.h"

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
    QString vehicleId = ui->vehicleIDLineEdit->text();
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
}
