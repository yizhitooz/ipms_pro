#include "chargerulewidget.h"
#include "ui_chargerulewidget.h"

ChargeRuleWidget::ChargeRuleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChargeRuleWidget)
{
    ui->setupUi(this);
    //限制只能输入两位小数浮点数
    QDoubleValidator* adoubleValidator = new QDoubleValidator(0, 0, 2, this);
    ui->moneyLineEdit->setValidator(adoubleValidator);
    set_method_label();
}

ChargeRuleWidget::~ChargeRuleWidget()
{
    delete ui;
}

void ChargeRuleWidget::on_changeButton_clicked()
{
    QString money = ui->moneyLineEdit->text();
    QString method = ui->comboBox->currentText();
    QString str = QString("update chargingmethod set money = %1 where chargingMethod = ").arg(money.toDouble());
    if(method == QString("每小时"))
    {
        str += QString("'hourly'");
    }
    if(method == QString("年卡"))
    {
        str += QString("'annual'");
    }
    if(method == QString("月卡"))
    {
        str += QString("'monthly'");
    }
    if(method == QString("季卡"))
    {
        str += QString("'quarterly'");
    }

    QSqlQuery query;
    if(query.exec(str))
    {
        QMessageBox::information(this,"提示","修改成功");
    }
    set_method_label();
    emit money_change();
}

void ChargeRuleWidget::set_method_label()
{

    QSqlQuery query("select * from chargingmethod");
    double moneys[4];
    int i = 0;
    while (query.next())
    {
        moneys[i] = query.value(2).toDouble();
        i++;
    }
    QString method_infomation = QString("年卡:%1元     季卡:%2元\n月卡:%3元    每15分钟:%1元").arg(moneys[0]).arg(moneys[1]).arg(moneys[2]).arg(moneys[3]);
    ui->methodLabel->setText(method_infomation);
}
