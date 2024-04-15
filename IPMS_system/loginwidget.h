#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

    int getLevel();
    void closeEvent(QCloseEvent *event);
signals:
    void level_sent(int level);
    void unlogin_close_signals();

private slots:
    void unlogin_close();

    void on_loginButton_clicked();

private:
    Ui::LoginWidget *ui;
    int level;
    bool islogin = false;
};

#endif // LOGINWIDGET_H
