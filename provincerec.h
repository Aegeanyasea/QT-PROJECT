#ifndef PROVINCEREC_H
#define PROVINCEREC_H

#include <QDialog>
#include<qlabel.h>
#include<QFileDialog>
#include<QDebug>
#include<QString>
#include<QPushButton>

namespace Ui {
class provincerec;
}

class provincerec : public QDialog
{
    Q_OBJECT

public:
    explicit provincerec(QWidget *parent = nullptr,QString ins_name="省份",QString ID0="show");
    QString provinceName;
    ~provincerec();
private slots:

    void on_openprovince_clicked();
    void travelclicked();

private:
    Ui::provincerec *ui;
    QPushButton *travel;
    QPushButton *open;
    QString ID;
};

#endif // PROVINCEREC_H
