#ifndef CHARGERULEWIDGET_H
#define CHARGERULEWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class ChargeRuleWidget;
}

class ChargeRuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChargeRuleWidget(QWidget *parent = nullptr);
    ~ChargeRuleWidget();

signals:
    void money_change();

private slots:
    void on_changeButton_clicked();

private:
    Ui::ChargeRuleWidget *ui;

    void set_method_label();
};

#endif // CHARGERULEWIDGET_H
