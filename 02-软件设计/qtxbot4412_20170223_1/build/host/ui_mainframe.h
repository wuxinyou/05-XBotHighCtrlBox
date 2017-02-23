/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created: Tue Feb 21 11:44:14 2017
**      by: Qt User Interface Compiler version 4.7.4
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

QT_BEGIN_NAMESPACE

class Ui_mainframe
{
public:
    QLabel *label;
    QLabel *label_4;

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
        QBrush brush3(QColor(236, 236, 236, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        QBrush brush4(QColor(118, 116, 108, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        mainframe->setPalette(palette);
        mainframe->setSizeGripEnabled(false);
        mainframe->setModal(true);
        label = new QLabel(mainframe);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(620, 270, 171, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        label->setPalette(palette1);
        label_4 = new QLabel(mainframe);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(680, 240, 111, 21));
        QFont font;
        font.setPointSize(16);
        label_4->setFont(font);

        retranslateUi(mainframe);

        QMetaObject::connectSlotsByName(mainframe);
    } // setupUi

    void retranslateUi(QDialog *mainframe)
    {
        mainframe->setWindowTitle(QApplication::translate("mainframe", "mainframe", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mainframe", "M1\357\274\232\345\215\225\345\205\263\350\212\202\346\216\247\345\210\266\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("mainframe", "00\357\274\23200\357\274\23200", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainframe: public Ui_mainframe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
