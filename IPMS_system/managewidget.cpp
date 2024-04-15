#include "managewidget.h"
#include "ui_managewidget.h"

ManageWidget::ManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageWidget)
{
    ui->setupUi(this);
    setComBox();
    ui->levelComboBox->addItem("0");
    ui->levelComboBox->addItem("1");
//    ui->levelComboBox->addItem("2");
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
    QSqlQuery query;
    QString str = QString("select * from authority where level < 2");
    query.exec(str);
    while (query.next())
    {
        ui->peopleComboBox->addItem(query.value(0).toString());
    }
}

void ManageWidget::setInformationLabel(const QString &text)
{
    if(text == QString("请选择人员"))
        return;
    QSqlQuery query;
    QString str = QString("select * from authority where managerID = %1").arg(text.toInt());
    query.exec(str);
    while (query.next())
    {
        QString label_text = QString("managerID:%1,level:%2").arg(query.value(0).toString()).arg(query.value(1).toString());
        ui->informationLabel->setText(label_text);
    }
}

void ManageWidget::on_changeButton_clicked()
{
    QString select_level = ui->levelComboBox->currentText();
    if(select_level == QString("权限等级"))
    {
        return;
    }
    QString people = ui->peopleComboBox->currentText();
    if(people == QString("请选择人员"))
    {
        return;
    }
    QSqlQuery query;
    QString str = QString("update authority set level = %1 where managerID = %2").arg(select_level.toInt()).arg(people.toInt());
    if(query.exec(str))
    {
        QMessageBox::information(this,"提示","修改成功");
    }
}
