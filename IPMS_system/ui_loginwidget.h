/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QLabel *label_title;
    QPushButton *loginButton;
    QLabel *label_2;
    QLineEdit *passworkLineEdit;
    QLineEdit *accountLineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_title02;
    QLabel *label;
    QLabel *label_5;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName(QString::fromUtf8("LoginWidget"));
        LoginWidget->setWindowModality(Qt::ApplicationModal);
        LoginWidget->resize(634, 537);
        LoginWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(92, 92, 92);\n"
""));
        label_title = new QLabel(LoginWidget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setGeometry(QRect(30, 120, 181, 41));
        label_title->setStyleSheet(QString::fromUtf8("color: rgb(247, 235, 183);\n"
"background-color: rgb(78, 78, 78\357\274\21480);\n"
"font: 18pt \"\345\215\216\346\226\207\350\241\214\346\245\267\";"));
        loginButton = new QPushButton(LoginWidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(120, 420, 121, 41));
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	background-color: rgb(123, 117, 69,30);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:20px;\n"
"        padding: 2px 2px;\n"
"    }\n"
"QPushButton:hover{\n"
"	background-color: rgb(123, 117, 69,90);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:20px;\n"
"        padding: 2px 2px;\n"
"    }"));
        label_2 = new QLabel(LoginWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(330, 0, 311, 611));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/prefix1/image/ground_2.jpg")));
        passworkLineEdit = new QLineEdit(LoginWidget);
        passworkLineEdit->setObjectName(QString::fromUtf8("passworkLineEdit"));
        passworkLineEdit->setGeometry(QRect(70, 340, 254, 41));
        passworkLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border-width:5px;\n"
"	border-style:solid;\n"
"	border-color:gray;\n"
"	border-radius:10px;\n"
"	padding: 0px 10px;\n"
"}"));
        accountLineEdit = new QLineEdit(LoginWidget);
        accountLineEdit->setObjectName(QString::fromUtf8("accountLineEdit"));
        accountLineEdit->setGeometry(QRect(70, 280, 254, 41));
        accountLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border-width:5px;\n"
"	border-style:solid;\n"
"	border-color:gray;\n"
"	border-radius:10px;\n"
"	padding: 0px 10px;\n"
"}"));
        label_3 = new QLabel(LoginWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 280, 51, 41));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/prefix1/image/icons8-login-50.png")));
        label_4 = new QLabel(LoginWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 330, 61, 61));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/prefix1/image/icons8-password-48.png")));
        label_title02 = new QLabel(LoginWidget);
        label_title02->setObjectName(QString::fromUtf8("label_title02"));
        label_title02->setGeometry(QRect(120, 180, 171, 51));
        label_title02->setStyleSheet(QString::fromUtf8("color: rgb(247, 235, 183);\n"
"background-color: rgb(78, 78, 78\357\274\21480);\n"
"font: 18pt \"\345\215\216\346\226\207\350\241\214\346\245\267\";"));
        label = new QLabel(LoginWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 81, 71));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(92, 92, 92\357\274\21480);"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/prefix1/image/icons8-parking-64.png")));
        label_5 = new QLabel(LoginWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(70, 10, 231, 51));
        label_5->setStyleSheet(QString::fromUtf8("font: 9pt \"\344\273\277\345\256\213\";\n"
"color: rgb(0, 138, 169);"));

        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QCoreApplication::translate("LoginWidget", "\347\231\273\345\275\225", nullptr));
        label_title->setText(QCoreApplication::translate("LoginWidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600; font-style:italic;\">\351\251\266\345\205\245\344\276\277\346\215\267</span></p></body></html>", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWidget", "Login Now", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_title02->setText(QCoreApplication::translate("LoginWidget", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600; font-style:italic;\">\351\251\266\345\207\272\347\225\205\351\200\232</span></p></body></html>", nullptr));
        label->setText(QString());
        label_5->setText(QCoreApplication::translate("LoginWidget", "<html><head/><body><p><span style=\" font-size:9pt;\">\346\231\272\350\203\275\345\201\234\350\275\246\347\256\241\347\220\206\347\263\273\347\273\237</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
