/********************************************************************************
** Form generated from reading UI file 'provincerec.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROVINCEREC_H
#define UI_PROVINCEREC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_provincerec
{
public:

    void setupUi(QDialog *provincerec)
    {
        if (provincerec->objectName().isEmpty())
            provincerec->setObjectName("provincerec");
        provincerec->resize(240, 279);

        retranslateUi(provincerec);

        QMetaObject::connectSlotsByName(provincerec);
    } // setupUi

    void retranslateUi(QDialog *provincerec)
    {
        provincerec->setWindowTitle(QCoreApplication::translate("provincerec", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class provincerec: public Ui_provincerec {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROVINCEREC_H
