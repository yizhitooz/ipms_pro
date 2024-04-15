/********************************************************************************
** Form generated from reading UI file 'chargerulewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGERULEWIDGET_H
#define UI_CHARGERULEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChargeRuleWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *methodLabel;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QLineEdit *moneyLineEdit;
    QLabel *label_2;
    QPushButton *changeButton;

    void setupUi(QWidget *ChargeRuleWidget)
    {
        if (ChargeRuleWidget->objectName().isEmpty())
            ChargeRuleWidget->setObjectName(QString::fromUtf8("ChargeRuleWidget"));
        ChargeRuleWidget->setWindowModality(Qt::ApplicationModal);
        ChargeRuleWidget->resize(400, 300);
        ChargeRuleWidget->setStyleSheet(QString::fromUtf8("color:rgb(78, 78, 78\357\274\21480);\n"
"background-color: rgb(247, 235, 183);\n"
""));
        verticalLayout = new QVBoxLayout(ChargeRuleWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        methodLabel = new QLabel(ChargeRuleWidget);
        methodLabel->setObjectName(QString::fromUtf8("methodLabel"));
        methodLabel->setStyleSheet(QString::fromUtf8("font: 16pt \"\344\273\277\345\256\213\";"));

        verticalLayout->addWidget(methodLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(ChargeRuleWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(0, 30));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox:!hover{\n"
"	background-color: rgb(255, 255, 255,30);\n"
"	font: 10pt \"\344\273\277\345\256\213\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }\n"
"QComboBox:hover{\n"
"	background-color: rgb(255, 255, 255,90);\n"
"	font: 10pt \"\344\273\277\345\256\213\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }"));

        horizontalLayout->addWidget(comboBox);

        moneyLineEdit = new QLineEdit(ChargeRuleWidget);
        moneyLineEdit->setObjectName(QString::fromUtf8("moneyLineEdit"));
        moneyLineEdit->setMinimumSize(QSize(0, 30));
        moneyLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border-width:2px;\n"
"	border-style:solid;\n"
"	border-color:gray;\n"
"	border-radius:10px;\n"
"	padding: 2px 2px;\n"
"}"));

        horizontalLayout->addWidget(moneyLineEdit);

        label_2 = new QLabel(ChargeRuleWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 30));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\344\273\277\345\256\213\";"));

        horizontalLayout->addWidget(label_2);

        changeButton = new QPushButton(ChargeRuleWidget);
        changeButton->setObjectName(QString::fromUtf8("changeButton"));
        changeButton->setMinimumSize(QSize(0, 30));
        changeButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 10pt \"\344\273\277\345\256\213\";\n"
"	background-color: rgb(123, 117, 69,70);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:hover{\n"
"	font: 10pt \"\344\273\277\345\256\213\";\n"
"	background-color: rgb(123, 117, 69,40);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:pressed{\n"
"	font: 10pt \"\344\273\277\345\256\213\";\n"
"	background-color: rgb(0, 0, 0,70);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }"));

        horizontalLayout->addWidget(changeButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);

        retranslateUi(ChargeRuleWidget);

        QMetaObject::connectSlotsByName(ChargeRuleWidget);
    } // setupUi

    void retranslateUi(QWidget *ChargeRuleWidget)
    {
        ChargeRuleWidget->setWindowTitle(QCoreApplication::translate("ChargeRuleWidget", "\346\224\266\350\264\271\350\247\204\345\210\231", nullptr));
        methodLabel->setText(QCoreApplication::translate("ChargeRuleWidget", "\346\224\266\350\264\271\350\247\204\345\210\231", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ChargeRuleWidget", "\346\257\217\345\260\217\346\227\266", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ChargeRuleWidget", "\345\271\264\345\215\241", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("ChargeRuleWidget", "\346\234\210\345\215\241", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("ChargeRuleWidget", "\345\255\243\345\215\241", nullptr));

        label_2->setText(QCoreApplication::translate("ChargeRuleWidget", "\345\205\203", nullptr));
        changeButton->setText(QCoreApplication::translate("ChargeRuleWidget", "\344\277\256\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChargeRuleWidget: public Ui_ChargeRuleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGERULEWIDGET_H
