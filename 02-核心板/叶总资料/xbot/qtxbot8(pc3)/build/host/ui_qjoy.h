/********************************************************************************
** Form generated from reading UI file 'qjoy.ui'
**
** Created: Thu Jul 25 13:59:21 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QJOY_H
#define UI_QJOY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qjoy
{
public:
    QPushButton *openJoyBtn;
    QLabel *label;
    QLabel *lbl_MSG;
    QLabel *lbl_buttonNum;
    QLabel *lbl_Pov;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;

    void setupUi(QWidget *qjoy)
    {
        if (qjoy->objectName().isEmpty())
            qjoy->setObjectName(QString::fromUtf8("qjoy"));
        qjoy->resize(640, 480);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(126, 126, 126, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        QBrush brush3(QColor(118, 116, 108, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        qjoy->setPalette(palette);
        openJoyBtn = new QPushButton(qjoy);
        openJoyBtn->setObjectName(QString::fromUtf8("openJoyBtn"));
        openJoyBtn->setGeometry(QRect(90, 40, 75, 23));
        label = new QLabel(qjoy);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(370, 130, 231, 301));
        lbl_MSG = new QLabel(qjoy);
        lbl_MSG->setObjectName(QString::fromUtf8("lbl_MSG"));
        lbl_MSG->setGeometry(QRect(40, 125, 511, 31));
        lbl_buttonNum = new QLabel(qjoy);
        lbl_buttonNum->setObjectName(QString::fromUtf8("lbl_buttonNum"));
        lbl_buttonNum->setGeometry(QRect(40, 195, 201, 31));
        lbl_Pov = new QLabel(qjoy);
        lbl_Pov->setObjectName(QString::fromUtf8("lbl_Pov"));
        lbl_Pov->setGeometry(QRect(40, 250, 221, 31));
        label_5 = new QLabel(qjoy);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 310, 241, 21));
        label_6 = new QLabel(qjoy);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 350, 261, 31));
        label_7 = new QLabel(qjoy);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 410, 261, 21));
        label_8 = new QLabel(qjoy);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(230, 30, 381, 31));

        retranslateUi(qjoy);

        QMetaObject::connectSlotsByName(qjoy);
    } // setupUi

    void retranslateUi(QWidget *qjoy)
    {
        qjoy->setWindowTitle(QApplication::translate("qjoy", "qjoy", 0, QApplication::UnicodeUTF8));
        openJoyBtn->setText(QApplication::translate("qjoy", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("qjoy", "TextLabel", 0, QApplication::UnicodeUTF8));
        lbl_MSG->setText(QApplication::translate("qjoy", "TextLabel", 0, QApplication::UnicodeUTF8));
        lbl_buttonNum->setText(QApplication::translate("qjoy", "TextLabel", 0, QApplication::UnicodeUTF8));
        lbl_Pov->setText(QApplication::translate("qjoy", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("qjoy", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("qjoy", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("qjoy", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("qjoy", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qjoy: public Ui_qjoy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QJOY_H
