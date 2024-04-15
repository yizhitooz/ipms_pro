#ifndef RECHARGEWIDGET_H
#define RECHARGEWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
namespace Ui {
class RechargeWidget;
}

class RechargeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RechargeWidget(QWidget *parent = nullptr);
    ~RechargeWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RechargeWidget *ui;
};

#endif // RECHARGEWIDGET_H
