/********************************************************************************
** Form generated from reading UI file 'rechargewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECHARGEWIDGET_H
#define UI_RECHARGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RechargeWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *vehicleIDLineEdit;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *annualRadioButton;
    QRadioButton *monthlyRadioButton;
    QRadioButton *quarterlyRadioButton;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *RechargeWidget)
    {
        if (RechargeWidget->objectName().isEmpty())
            RechargeWidget->setObjectName(QString::fromUtf8("RechargeWidget"));
        RechargeWidget->setWindowModality(Qt::ApplicationModal);
        RechargeWidget->resize(400, 300);
        RechargeWidget->setStyleSheet(QString::fromUtf8("\n"
"color:rgb(78, 78, 78\357\274\21480);\n"
"background-color: rgb(247, 235, 183);\n"
"\n"
""));
        verticalLayout_2 = new QVBoxLayout(RechargeWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(RechargeWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\346\261\211\344\273\252\346\226\207\351\273\221-65W\";\n"
"color:rgb(54, 54, 54)"));

        horizontalLayout->addWidget(label);

        vehicleIDLineEdit = new QLineEdit(RechargeWidget);
        vehicleIDLineEdit->setObjectName(QString::fromUtf8("vehicleIDLineEdit"));
        vehicleIDLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border-width:2px;\n"
"	border-style:solid;\n"
"	border-color:gray;\n"
"	border-radius:10px;\n"
"	padding: 2px 2px;\n"
"}"));

        horizontalLayout->addWidget(vehicleIDLineEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBox = new QGroupBox(RechargeWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        annualRadioButton = new QRadioButton(groupBox);
        annualRadioButton->setObjectName(QString::fromUtf8("annualRadioButton"));
        annualRadioButton->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\261\211\344\273\252\346\226\207\351\273\221-85W"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        annualRadioButton->setFont(font);
        annualRadioButton->setStyleSheet(QString::fromUtf8("font: 12pt \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";\n"
"color: rgb(54, 54, 54);"));

        verticalLayout->addWidget(annualRadioButton);

        monthlyRadioButton = new QRadioButton(groupBox);
        monthlyRadioButton->setObjectName(QString::fromUtf8("monthlyRadioButton"));
        monthlyRadioButton->setMinimumSize(QSize(0, 30));
        monthlyRadioButton->setStyleSheet(QString::fromUtf8("font: 12pt \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";\n"
"color: rgb(54, 54, 54);"));

        verticalLayout->addWidget(monthlyRadioButton);

        quarterlyRadioButton = new QRadioButton(groupBox);
        quarterlyRadioButton->setObjectName(QString::fromUtf8("quarterlyRadioButton"));
        quarterlyRadioButton->setMinimumSize(QSize(0, 30));
        quarterlyRadioButton->setStyleSheet(QString::fromUtf8("font: 12pt \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";\n"
"color: rgb(54, 54, 54);"));

        verticalLayout->addWidget(quarterlyRadioButton);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\261\211\344\273\252\346\226\207\351\273\221-85W"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setItalic(false);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 14pt  \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";\n"
"	background-color: rgb(255, 255, 255,70);\n"
"	\n"
"	color: rgb(170, 170, 0);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:hover{\n"
"	font: 14pt  \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";\n"
"	background-color: rgb(123, 117, 69,70);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:pressed{\n"
"	font: 14pt \"\346\261\211\344\273\252\346\226\207\351\273\221-85W\";\n"
"	background-color: rgb(123, 117, 69,40);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(groupBox);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 3);

        retranslateUi(RechargeWidget);

        QMetaObject::connectSlotsByName(RechargeWidget);
    } // setupUi

    void retranslateUi(QWidget *RechargeWidget)
    {
        RechargeWidget->setWindowTitle(QCoreApplication::translate("RechargeWidget", "\345\205\205\345\200\274\347\225\214\351\235\242", nullptr));
        label->setText(QCoreApplication::translate("RechargeWidget", "\350\275\246\347\211\214\345\217\267:", nullptr));
        groupBox->setTitle(QString());
        annualRadioButton->setText(QCoreApplication::translate("RechargeWidget", "\345\271\264\345\215\241(365\345\244\251)", nullptr));
        monthlyRadioButton->setText(QCoreApplication::translate("RechargeWidget", "\346\234\210\345\215\241(30\345\244\251)", nullptr));
        quarterlyRadioButton->setText(QCoreApplication::translate("RechargeWidget", "\345\255\243\345\215\241(90\345\244\251)", nullptr));
        pushButton->setText(QCoreApplication::translate("RechargeWidget", "\345\205\205\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RechargeWidget: public Ui_RechargeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECHARGEWIDGET_H
