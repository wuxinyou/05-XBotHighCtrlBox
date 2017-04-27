/********************************************************************************
** Form generated from reading UI file 'videoDis.ui'
**
** Created: Thu Mar 28 14:23:21 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEODIS_H
#define UI_VIDEODIS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include "Qtcustom/avideo.h"

QT_BEGIN_NAMESPACE

class Ui_videoDis
{
public:
    AVideo *myAvideo;

    void setupUi(QWidget *videoDis)
    {
        if (videoDis->objectName().isEmpty())
            videoDis->setObjectName(QString::fromUtf8("videoDis"));
        videoDis->resize(800, 320);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(118, 116, 108, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        videoDis->setPalette(palette);
        myAvideo = new AVideo(videoDis);
        myAvideo->setObjectName(QString::fromUtf8("myAvideo"));
        myAvideo->setEnabled(true);
        myAvideo->setGeometry(QRect(0, 24, 800, 296));
        myAvideo->setAutostart(true);

        retranslateUi(videoDis);

        QMetaObject::connectSlotsByName(videoDis);
    } // setupUi

    void retranslateUi(QWidget *videoDis)
    {
        videoDis->setWindowTitle(QApplication::translate("videoDis", "videoDis", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class videoDis: public Ui_videoDis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEODIS_H
