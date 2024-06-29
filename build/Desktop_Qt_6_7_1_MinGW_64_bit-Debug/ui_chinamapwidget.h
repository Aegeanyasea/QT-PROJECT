/********************************************************************************
** Form generated from reading UI file 'chinamapwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHINAMAPWIDGET_H
#define UI_CHINAMAPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChinaMapWidget
{
public:

    void setupUi(QWidget *ChinaMapWidget)
    {
        if (ChinaMapWidget->objectName().isEmpty())
            ChinaMapWidget->setObjectName("ChinaMapWidget");
        ChinaMapWidget->resize(527, 408);

        retranslateUi(ChinaMapWidget);

        QMetaObject::connectSlotsByName(ChinaMapWidget);
    } // setupUi

    void retranslateUi(QWidget *ChinaMapWidget)
    {
        ChinaMapWidget->setWindowTitle(QCoreApplication::translate("ChinaMapWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChinaMapWidget: public Ui_ChinaMapWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHINAMAPWIDGET_H
