/********************************************************************************
** Form generated from reading UI file 'managewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEWIDGET_H
#define UI_MANAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageWidget
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QComboBox *peopleComboBox;
    QLabel *informationLabel;
    QComboBox *levelComboBox;
    QPushButton *changeButton;

    void setupUi(QWidget *ManageWidget)
    {
        if (ManageWidget->objectName().isEmpty())
            ManageWidget->setObjectName(QString::fromUtf8("ManageWidget"));
        ManageWidget->setWindowModality(Qt::ApplicationModal);
        ManageWidget->resize(400, 300);
        ManageWidget->setStyleSheet(QString::fromUtf8("\n"
"color:rgb(78, 78, 78\357\274\21480);\n"
"background-color: rgb(247, 235, 183);\n"
""));
        verticalLayout = new QVBoxLayout(ManageWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(ManageWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("	font: 75 10pt \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";"));

        verticalLayout->addWidget(pushButton);

        peopleComboBox = new QComboBox(ManageWidget);
        peopleComboBox->addItem(QString());
        peopleComboBox->setObjectName(QString::fromUtf8("peopleComboBox"));
        peopleComboBox->setStyleSheet(QString::fromUtf8("\n"
"QComboBox:!hover{\n"
"	background-color: rgb(255, 255, 255,30);\n"
"	font: 14pt \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }\n"
"QComboBox:hover{\n"
"	background-color: rgb(255, 255, 255,90);\n"
"	font: 14pt \"\344\273\277\345\256\213\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }"));

        verticalLayout->addWidget(peopleComboBox);

        informationLabel = new QLabel(ManageWidget);
        informationLabel->setObjectName(QString::fromUtf8("informationLabel"));
        informationLabel->setStyleSheet(QString::fromUtf8("	font: 16pt \"\346\261\211\344\273\252\346\226\207\351\273\221-65W\";"));

        verticalLayout->addWidget(informationLabel);

        levelComboBox = new QComboBox(ManageWidget);
        levelComboBox->addItem(QString());
        levelComboBox->setObjectName(QString::fromUtf8("levelComboBox"));
        levelComboBox->setStyleSheet(QString::fromUtf8("\n"
"QComboBox:!hover{\n"
"	background-color: rgb(255, 255, 255,30);\n"
"	font: 14pt \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }\n"
"QComboBox:hover{\n"
"	background-color: rgb(255, 255, 255,90);\n"
"	font: 14pt \"\344\273\277\345\256\213\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }"));

        verticalLayout->addWidget(levelComboBox);

        changeButton = new QPushButton(ManageWidget);
        changeButton->setObjectName(QString::fromUtf8("changeButton"));
        changeButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	background-color: rgb(123, 117, 69,30);\n"
"	font: 75 16pt \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:10px;\n"
"        padding: 2px 2px;\n"
"    }\n"
"QPushButton:hover{\n"
"	background-color: rgb(123, 117, 69,90);\n"
"	font: 16pt \"\344\273\277\345\256\213\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:10px;\n"
"        padding: 2px 2px;\n"
"    }"));

        verticalLayout->addWidget(changeButton);


        retranslateUi(ManageWidget);

        QMetaObject::connectSlotsByName(ManageWidget);
    } // setupUi

    void retranslateUi(QWidget *ManageWidget)
    {
        ManageWidget->setWindowTitle(QCoreApplication::translate("ManageWidget", "\347\256\241\347\220\206", nullptr));
        pushButton->setText(QCoreApplication::translate("ManageWidget", "\345\210\267\346\226\260\344\272\272\345\221\230\345\210\227\350\241\250", nullptr));
        peopleComboBox->setItemText(0, QCoreApplication::translate("ManageWidget", "\350\257\267\351\200\211\346\213\251\344\272\272\345\221\230", nullptr));

        informationLabel->setText(QCoreApplication::translate("ManageWidget", "\344\272\272\345\221\230\344\277\241\346\201\257", nullptr));
        levelComboBox->setItemText(0, QCoreApplication::translate("ManageWidget", "\346\235\203\351\231\220\347\255\211\347\272\247", nullptr));

        changeButton->setText(QCoreApplication::translate("ManageWidget", "\344\277\256\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManageWidget: public Ui_ManageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEWIDGET_H
