#ifndef MANAGEWIDGET_H
#define MANAGEWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class ManageWidget;
}

class ManageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManageWidget(QWidget *parent = nullptr);
    ~ManageWidget();

    void setComBox();

private slots:
    void setInformationLabel(const QString &text);

    void on_changeButton_clicked();

private:
    Ui::ManageWidget *ui;
};

#endif // MANAGEWIDGET_H
