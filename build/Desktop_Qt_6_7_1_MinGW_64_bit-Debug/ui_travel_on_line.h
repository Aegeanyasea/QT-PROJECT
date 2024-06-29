/********************************************************************************
** Form generated from reading UI file 'travel_on_line.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAVEL_ON_LINE_H
#define UI_TRAVEL_ON_LINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_travel_on_line
{
public:

    void setupUi(QWidget *travel_on_line)
    {
        if (travel_on_line->objectName().isEmpty())
            travel_on_line->setObjectName("travel_on_line");
        travel_on_line->resize(400, 300);

        retranslateUi(travel_on_line);

        QMetaObject::connectSlotsByName(travel_on_line);
    } // setupUi

    void retranslateUi(QWidget *travel_on_line)
    {
        travel_on_line->setWindowTitle(QCoreApplication::translate("travel_on_line", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class travel_on_line: public Ui_travel_on_line {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAVEL_ON_LINE_H
