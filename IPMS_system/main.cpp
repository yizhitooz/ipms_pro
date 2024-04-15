#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    LoginWidget login_widget;
    login_widget.show();
    QObject::connect(&login_widget,SIGNAL(level_sent(int)),&w,SLOT(level_rec_from_login(int)));
    QObject::connect(&login_widget,&LoginWidget::unlogin_close_signals,&w,&MainWindow::unlogin);
    return a.exec();

}
