/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnEasyMode;
    QPushButton *btnMediumMode;
    QPushButton *btnHardMode;
    QPushButton *btnExpertMode;
    QLabel *logoGear;
    QLabel *labelRAM;
    QLabel *labelRAMName;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnEasyMode = new QPushButton(centralwidget);
        btnEasyMode->setObjectName("btnEasyMode");
        btnEasyMode->setGeometry(QRect(100, 250, 120, 50));
        btnMediumMode = new QPushButton(centralwidget);
        btnMediumMode->setObjectName("btnMediumMode");
        btnMediumMode->setGeometry(QRect(260, 250, 120, 50));
        btnHardMode = new QPushButton(centralwidget);
        btnHardMode->setObjectName("btnHardMode");
        btnHardMode->setGeometry(QRect(420, 250, 120, 50));
        btnExpertMode = new QPushButton(centralwidget);
        btnExpertMode->setObjectName("btnExpertMode");
        btnExpertMode->setGeometry(QRect(580, 250, 120, 50));
        logoGear = new QLabel(centralwidget);
        logoGear->setObjectName("logoGear");
        logoGear->setGeometry(QRect(30, 20, 241, 191));
        labelRAM = new QLabel(centralwidget);
        labelRAM->setObjectName("labelRAM");
        labelRAM->setGeometry(QRect(510, 70, 150, 100));
        labelRAMName = new QLabel(centralwidget);
        labelRAMName->setObjectName("labelRAMName");
        labelRAMName->setGeometry(QRect(510, 0, 150, 100));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnEasyMode->setText(QCoreApplication::translate("MainWindow", "Easy", nullptr));
        btnMediumMode->setText(QCoreApplication::translate("MainWindow", "Medium", nullptr));
        btnHardMode->setText(QCoreApplication::translate("MainWindow", "Hard", nullptr));
        btnExpertMode->setText(QCoreApplication::translate("MainWindow", "Expert", nullptr));
        logoGear->setText(QString());
        labelRAM->setText(QString());
        labelRAMName->setText(QCoreApplication::translate("MainWindow", "RAM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
