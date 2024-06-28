#include "provincerec.h"
#include "ui_provincerec.h"
#include<QDebug>
#include "provinceinfodialog.h"
#include "travel_on_line.h"
#include<QPushButton>
#include<QString>
#include <QVBoxLayout>

provincerec::provincerec(QWidget *parent,QString ins_name,QString ID0)
    : QDialog(parent)
    , ui(new Ui::provincerec)
{
    provinceName=ins_name;
    ID=ID0;
    ui->setupUi(this);
    travel = new QPushButton("云游" + provinceName, this);
    travel->setStyleSheet(
        "QPushButton { background-color: #F5F6F9; color: black; border-radius: 5px; padding: 10px; font-size: 16px; font-weight: bold; }"
        "QPushButton:hover { background-color: #EAEFFF; }"
        );
    travel->setGeometry(50, 50, 200, 50); // 设置按钮的位置和大小

    connect(travel,&QPushButton::clicked,this,&provincerec::travelclicked);
    travel->move(61,67);

    open=new QPushButton("查看日志",this);
    open->setStyleSheet(
        "QPushButton { background-color: #F5F6F9; color: black; border-radius: 5px solid; padding: 10px;font-size: 16px; font-weight: bold; }"
        "QPushButton:hover { background-color: #EAEFFF; }"
        );
    open->setGeometry(50, 50, 200, 50); // 设置按钮的位置和大小
    // 创建布局并将按钮添加到布局中
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(travel);
    layout->addWidget(open);
    layout->setAlignment(travel, Qt::AlignCenter); // 设置按钮居中对齐
    layout->setAlignment(open, Qt::AlignCenter);   // 设置按钮居中对齐

    connect(open,&QPushButton::clicked,this,&provincerec::on_openprovince_clicked);
    open->move(61,134);
    resize(200,220);
    setWindowTitle(provinceName);
}

provincerec::~provincerec()
{
    delete ui;
}

void provincerec::on_openprovince_clicked()
{
    ProvinceInfoDialog* dialog = new ProvinceInfoDialog(this);
    QString provinceInfo = "please fill in your travel record in" + provinceName;

    //加载文件内容；
    QString filePath=QApplication::applicationDirPath()+"/"+provinceName+ID+".txt";
    QFile file(filePath);
    QString savedContent;
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        savedContent = in.readAll();
        file.close();
    }else{
        savedContent = provinceInfo;
    }
    dialog->setProvinceInfo(provinceName, savedContent,ID);
    dialog->exec();
}

void provincerec::travelclicked(){
    travel_on_line *line=new travel_on_line(NULL,provinceName);
    line->show();
}
