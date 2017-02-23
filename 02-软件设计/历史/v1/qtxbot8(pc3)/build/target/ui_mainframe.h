/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created: Tue Jul 31 09:59:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include "Qtcustom/avideo.h"
#include "Qtcustom/serialport.h"

QT_BEGIN_NAMESPACE

class Ui_mainframe
{
public:
    SerialPort *serialport;
    QLabel *label;
    QLabel *label_4;
    AVideo *avideo;

    void setupUi(QDialog *mainframe)
    {
        if (mainframe->objectName().isEmpty())
            mainframe->setObjectName(QString::fromUtf8("mainframe"));
        mainframe->setWindowModality(Qt::NonModal);
        mainframe->resize(800, 300);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(94, 100, 81, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush3(QColor(118, 116, 108, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        mainframe->setPalette(palette);
        mainframe->setSizeGripEnabled(false);
        mainframe->setModal(true);
        serialport = new SerialPort(mainframe);
        serialport->setObjectName(QString::fromUtf8("serialport"));
        serialport->setGeometry(QRect(560, 10, 32, 32));
        serialport->setMaximumSize(QSize(32, 32));
        serialport->setInputMethodHints(Qt::ImhNone);
        serialport->setPort(0u);
        serialport->setBaudrate(SerialPort::BAUD19200);
        serialport->setProperty("paritytype", QVariant(SerialPort::NONE));
        serialport->setTimeout(1u);
        serialport->setAutoOpen(false);
        label = new QLabel(mainframe);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(620, 279, 51, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label->setPalette(palette1);
        label_4 = new QLabel(mainframe);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(740, 280, 61, 21));
        avideo = new AVideo(mainframe);
        avideo->setObjectName(QString::fromUtf8("avideo"));
        avideo->setGeometry(QRect(690, 50, 80, 80));
        avideo->setAutostart(true);

        retranslateUi(mainframe);

        QMetaObject::connectSlotsByName(mainframe);
    } // setupUi

    void retranslateUi(QDialog *mainframe)
    {
        mainframe->setWindowTitle(QApplication::translate("mainframe", "mainframe", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mainframe", "1.23h", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("mainframe", "00\357\274\23200\357\274\23200", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainframe: public Ui_mainframe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
