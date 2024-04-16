/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *rechargePageButton;
    QPushButton *inAndOutPageButton;
    QPushButton *garagePageButton;
    QPushButton *queryPageButton;
    QPushButton *chargeRulePageButton;
    QPushButton *managePageButton;
    QStackedWidget *stackedWidget;
    QWidget *inAndOutPage;
    QPushButton *inButton;
    QPushButton *outButton;
    QLabel *spaceLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QLineEdit *vehicleIDLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QLineEdit *placeLineEdit;
    QLabel *billLabel;
    QWidget *informationPage;
    QVBoxLayout *verticalLayout_3;
    QPushButton *AllInformatioButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *informationVehicleIDLineEdit;
    QLabel *label_6;
    QDateEdit *dateEdit;
    QPushButton *informationSearchButton;
    QTableView *informationTableView;
    QWidget *garagePage;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_16;
    QPushButton *refreshButton;
    QTableView *garageTableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setStyleSheet(QString::fromUtf8("#MainWindow\n"
"{\n"
"background-image: url(:/prefix1/image/parking_mainwindow.jpg);\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255,90);"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        rechargePageButton = new QPushButton(groupBox);
        rechargePageButton->setObjectName(QString::fromUtf8("rechargePageButton"));
        rechargePageButton->setMinimumSize(QSize(0, 75));
        rechargePageButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(255, 255, 255\357\274\21470);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,70);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:pressed{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,40);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }"));

        verticalLayout->addWidget(rechargePageButton);

        inAndOutPageButton = new QPushButton(groupBox);
        inAndOutPageButton->setObjectName(QString::fromUtf8("inAndOutPageButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inAndOutPageButton->sizePolicy().hasHeightForWidth());
        inAndOutPageButton->setSizePolicy(sizePolicy);
        inAndOutPageButton->setMinimumSize(QSize(0, 75));
        inAndOutPageButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(255, 255, 255\357\274\21470);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,70);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:pressed{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,40);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }"));

        verticalLayout->addWidget(inAndOutPageButton);

        garagePageButton = new QPushButton(groupBox);
        garagePageButton->setObjectName(QString::fromUtf8("garagePageButton"));
        garagePageButton->setMinimumSize(QSize(0, 75));
        garagePageButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(255, 255, 255\357\274\21470);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,70);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:pressed{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,40);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }"));

        verticalLayout->addWidget(garagePageButton);

        queryPageButton = new QPushButton(groupBox);
        queryPageButton->setObjectName(QString::fromUtf8("queryPageButton"));
        queryPageButton->setMinimumSize(QSize(0, 75));
        queryPageButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(255, 255, 255\357\274\21470);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,70);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:pressed{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,40);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }"));

        verticalLayout->addWidget(queryPageButton);

        chargeRulePageButton = new QPushButton(groupBox);
        chargeRulePageButton->setObjectName(QString::fromUtf8("chargeRulePageButton"));
        chargeRulePageButton->setMinimumSize(QSize(0, 75));
        chargeRulePageButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(255, 255, 255\357\274\21470);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,70);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:pressed{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,40);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }"));

        verticalLayout->addWidget(chargeRulePageButton);

        managePageButton = new QPushButton(groupBox);
        managePageButton->setObjectName(QString::fromUtf8("managePageButton"));
        managePageButton->setMinimumSize(QSize(0, 75));
        managePageButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(255, 255, 255\357\274\21470);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:hover{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,70);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }\n"
"QPushButton:pressed{\n"
"	font: 75 10pt \"Agency FB\";\n"
"	background-color: rgb(123, 117, 69,40);\n"
"	color: rgb(242, 230, 172);\n"
"        border-width:1px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 1px 1px;\n"
"    }"));

        verticalLayout->addWidget(managePageButton);


        horizontalLayout->addWidget(groupBox);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        inAndOutPage = new QWidget();
        inAndOutPage->setObjectName(QString::fromUtf8("inAndOutPage"));
        inButton = new QPushButton(inAndOutPage);
        inButton->setObjectName(QString::fromUtf8("inButton"));
        inButton->setGeometry(QRect(40, 410, 101, 51));
        inButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	background-color: rgb(123, 117, 69,30);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }\n"
"QPushButton:hover{\n"
"	background-color: rgb(123, 117, 69,90);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }"));
        outButton = new QPushButton(inAndOutPage);
        outButton->setObjectName(QString::fromUtf8("outButton"));
        outButton->setGeometry(QRect(200, 410, 101, 51));
        outButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	background-color: rgb(123, 117, 69,30);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }\n"
"QPushButton:hover{\n"
"	background-color: rgb(123, 117, 69,90);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }"));
        spaceLabel = new QLabel(inAndOutPage);
        spaceLabel->setObjectName(QString::fromUtf8("spaceLabel"));
        spaceLabel->setGeometry(QRect(50, 30, 241, 141));
        layoutWidget = new QWidget(inAndOutPage);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 250, 271, 131));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        vehicleIDLineEdit = new QLineEdit(layoutWidget);
        vehicleIDLineEdit->setObjectName(QString::fromUtf8("vehicleIDLineEdit"));
        vehicleIDLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border-width:2px;\n"
"	border-style:solid;\n"
"	border-color:gray;\n"
"	border-radius:10px;\n"
"	padding: 2px 2px;\n"
"}"));

        horizontalLayout_2->addWidget(vehicleIDLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_6->addWidget(label_8);

        placeLineEdit = new QLineEdit(layoutWidget);
        placeLineEdit->setObjectName(QString::fromUtf8("placeLineEdit"));
        placeLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border-width:2px;\n"
"	border-style:solid;\n"
"	border-color:gray;\n"
"	border-radius:10px;\n"
"	padding: 2px 2px;\n"
"}"));

        horizontalLayout_6->addWidget(placeLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_6);

        billLabel = new QLabel(inAndOutPage);
        billLabel->setObjectName(QString::fromUtf8("billLabel"));
        billLabel->setGeometry(QRect(360, 130, 301, 291));
        stackedWidget->addWidget(inAndOutPage);
        informationPage = new QWidget();
        informationPage->setObjectName(QString::fromUtf8("informationPage"));
        verticalLayout_3 = new QVBoxLayout(informationPage);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        AllInformatioButton = new QPushButton(informationPage);
        AllInformatioButton->setObjectName(QString::fromUtf8("AllInformatioButton"));
        AllInformatioButton->setStyleSheet(QString::fromUtf8("font: 12pt \"\344\273\277\345\256\213\";"));

        verticalLayout_3->addWidget(AllInformatioButton);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(informationPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(123, 117, 69,99);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(242, 230, 172);"));

        horizontalLayout_4->addWidget(label);

        informationVehicleIDLineEdit = new QLineEdit(informationPage);
        informationVehicleIDLineEdit->setObjectName(QString::fromUtf8("informationVehicleIDLineEdit"));
        informationVehicleIDLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border-width:2px;\n"
"	border-style:solid;\n"
"	border-color:gray;\n"
"	border-radius:10px;\n"
"	padding: 2px 2px;\n"
"}"));

        horizontalLayout_4->addWidget(informationVehicleIDLineEdit);

        label_6 = new QLabel(informationPage);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(123, 117, 69,99);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(242, 230, 172);"));

        horizontalLayout_4->addWidget(label_6);

        dateEdit = new QDateEdit(informationPage);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setDateTime(QDateTime(QDate(2023, 1, 1), QTime(0, 0, 1)));

        horizontalLayout_4->addWidget(dateEdit);

        informationSearchButton = new QPushButton(informationPage);
        informationSearchButton->setObjectName(QString::fromUtf8("informationSearchButton"));
        informationSearchButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	background-color: rgb(123, 117, 69,30);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }\n"
"QPushButton:hover{\n"
"	background-color: rgb(123, 117, 69,90);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }"));

        horizontalLayout_4->addWidget(informationSearchButton);


        verticalLayout_3->addLayout(horizontalLayout_4);

        informationTableView = new QTableView(informationPage);
        informationTableView->setObjectName(QString::fromUtf8("informationTableView"));

        verticalLayout_3->addWidget(informationTableView);

        stackedWidget->addWidget(informationPage);
        garagePage = new QWidget();
        garagePage->setObjectName(QString::fromUtf8("garagePage"));
        verticalLayout_2 = new QVBoxLayout(garagePage);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_16 = new QLabel(garagePage);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setStyleSheet(QString::fromUtf8("background-color: rgb(123, 117, 69,99);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(242, 230, 172);"));

        horizontalLayout_3->addWidget(label_16);

        refreshButton = new QPushButton(garagePage);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	background-color: rgb(123, 117, 69,30);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }\n"
"QPushButton:hover{\n"
"	background-color: rgb(123, 117, 69,90);\n"
"	font: 75 10pt \"Agency FB\";\n"
"	color: rgb(0, 0, 0);\n"
"        border-width:2px;\n"
"        border-style:solid;\n"
"        border-color:gray;\n"
"        border-radius:5px;\n"
"        padding: 2px 2px;\n"
"    }"));

        horizontalLayout_3->addWidget(refreshButton);


        verticalLayout_2->addLayout(horizontalLayout_3);

        garageTableView = new QTableView(garagePage);
        garageTableView->setObjectName(QString::fromUtf8("garageTableView"));

        verticalLayout_2->addWidget(garageTableView);

        stackedWidget->addWidget(garagePage);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\201\234\350\275\246\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        groupBox->setTitle(QString());
        rechargePageButton->setText(QCoreApplication::translate("MainWindow", "\345\205\205\345\200\274", nullptr));
        inAndOutPageButton->setText(QCoreApplication::translate("MainWindow", "\345\207\272\345\205\245\345\234\272\347\256\241\347\220\206", nullptr));
        garagePageButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\350\275\246\345\272\223", nullptr));
        queryPageButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\345\216\206\345\217\262\n"
"\345\201\234\350\275\246\344\277\241\346\201\257", nullptr));
        chargeRulePageButton->setText(QCoreApplication::translate("MainWindow", "\346\224\266\350\264\271\350\247\204\345\210\231", nullptr));
        managePageButton->setText(QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206", nullptr));
        inButton->setText(QCoreApplication::translate("MainWindow", "\345\205\245\345\234\272", nullptr));
        outButton->setText(QCoreApplication::translate("MainWindow", "\345\207\272\345\234\272", nullptr));
        spaceLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600; color:#318eff;\">\350\275\246\344\275\215\344\275\231\351\207\217</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\275\246\347\211\214\345\217\267:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\346\243\200\346\237\245\345\217\243:", nullptr));
        billLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">\345\207\272\345\205\245\345\234\272\344\277\241\346\201\257</span></p></body></html>", nullptr));
        AllInformatioButton->setText(QCoreApplication::translate("MainWindow", "\345\216\206\345\217\262\345\201\234\350\275\246\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\275\246\347\211\214\345\217\267:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\346\227\245\346\234\237", nullptr));
        informationSearchButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\345\275\223\345\211\215\350\275\246\345\272\223\350\275\246\350\276\206\345\210\227\350\241\250</p></body></html>", nullptr));
        refreshButton->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
