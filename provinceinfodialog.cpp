
#include "provinceinfodialog.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include<QApplication>
#include<QMessageBox>
#include<QTimer>
#include<QGraphicsOpacityEffect>
#include<QTimer>

ProvinceInfoDialog::ProvinceInfoDialog(QWidget* parent)
    : QDialog(parent){
    nameLabel = new QLabel(this);
    infoTextEdit = new QPlainTextEdit(this);
    saveButton = new QPushButton("Save", this);
    imageButton = new QPushButton("Loadimage",this);
    image = new QLabel(this);
    changeButton= new QPushButton("changeimage",this);

    // 设置按钮样式
    saveButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border-radius: 5px; padding: 10px; }"
                              "QPushButton:hover { background-color: #45a049; }");
    imageButton->setStyleSheet("QPushButton { background-color: #008CBA; color: white; border-radius: 5px; padding: 10px; }"
                               "QPushButton:hover { background-color: #007B9D; }");
    changeButton->setStyleSheet("QPushButton { background-color: rgba(255, 0, 0, 150); color: white; border-radius: 5px; padding: 10px; }"
                                "QPushButton:hover { background-color: #FF0000; }");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(image);
    layout->addWidget(nameLabel);
    layout->addWidget(infoTextEdit);
    layout->addWidget(saveButton);
    layout->addWidget(imageButton);
    layout->addWidget(changeButton);

    setLayout(layout);

    image->setFixedSize(400, 528); // 设置头像标签的固定大小
    image->setAlignment(Qt::AlignCenter); // 添加边框以示预留空间

    connect(saveButton, &QPushButton::clicked, this, &ProvinceInfoDialog::saveButtonClicked);
    connect(imageButton, &QPushButton::clicked, this, &ProvinceInfoDialog::imageButtonClicked);
    connect(changeButton,&QPushButton::clicked,this, &ProvinceInfoDialog::changeButtonClicked);
}

void ProvinceInfoDialog::setProvinceInfo(const QString& provinceName, const QString& provinceInfo,QString ID0) {
    nameLabel->setText("province: " + provinceName);
    QString filename=provinceName;
    infoTextEdit->setPlainText(provinceInfo);
    this->provincename=provinceName;
    this->ID=ID0;

    QString filePath=QApplication::applicationDirPath()+"/"+this->provincename+ID+".txt";
    QFile file(filePath);
    QString savedCount;
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        savedCount=in.readAll();
        file.close();
    }
    infoTextEdit->setPlainText(savedCount);
    QString filePath0=QApplication::applicationDirPath()+"/"+this->provincename+"picture"+ID+".txt";
    QFile file0(filePath0);
    if(file0.open(QIODevice::ReadOnly)){
        QTextStream in1(&file0);
        in1>>num;
        in1.readLine();
        while(!in1.atEnd()){
            imageName.append(in1.readLine());
        }
        file0.close();
    }
    changeButtonClicked();

    time=new QTimer(this);
    connect(time,&QTimer::timeout,this,&ProvinceInfoDialog::changeButtonClicked);
    time->start(12000);
    setupanimation();
    changeButtonClicked();
}

void ProvinceInfoDialog::saveButtonClicked() {
    QString filePath = QApplication::applicationDirPath()+"/"+this->provincename+ID+".txt";
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out<<infoTextEdit->toPlainText();
        file.close();
    }
    QString filePath0 =QApplication::applicationDirPath()+"/"+this->provincename+"picture"+ID+".txt";
    QFile file0(filePath0);
    if(file0.open(QIODevice::WriteOnly)){
        QTextStream out(&file0);
        out<<this->num<<"\n";
        for(const QString& str:imageName){
            out<<str<<"\n";
        }
        file0.close();
        QMessageBox* msg=new QMessageBox(this);
        msg->setWindowTitle("info");
        msg->setText("saved successfully");
        msg->setStandardButtons(QMessageBox::Cancel);
        msg->setIcon(QMessageBox::Information);
        msg->show();

        QTimer::singleShot(1,msg,&QMessageBox::close);
    }
}

void ProvinceInfoDialog::imageButtonClicked(){
    QString filename=QFileDialog::getOpenFileName(this,tr("open image"),QDir::homePath(),tr("(*.jpg)\n(*.bmp)\n(*.png)"));
    qDebug()<<"filename:"<<filename;
    QImage ima=QImage(filename);
    qDebug()<<"image:"<<ima;
    image->setPixmap(QPixmap::fromImage(ima).scaled(400,528));
    imageName.append(filename);
    num++;
}

void ProvinceInfoDialog::changeButtonClicked(){
    if(num==0){
        return;
    }
    QString filename=imageName.at(now);
    now++;
    now=now%num;
    setupanimation();
    Fadeout->start();
}

void ProvinceInfoDialog::setupanimation(){
    QGraphicsOpacityEffect *effect=new QGraphicsOpacityEffect(this);
    image->setGraphicsEffect(effect);

    Fadeout =new QPropertyAnimation(effect,"opacity");
    Fadeout->setDuration(1000);
    Fadeout->setStartValue(1.0);
    Fadeout->setEndValue(0.0);

    Fadein=new QPropertyAnimation(effect,"opacity");
    Fadein->setDuration(1000);
    Fadein->setStartValue(0.0);
    Fadein->setEndValue(1.0);

    connect(Fadeout,&QPropertyAnimation::finished,[this]{
        QString filename=imageName.at(now);
        QImage imageshow=QImage(filename);
        image->setPixmap(QPixmap::fromImage(imageshow).scaled(400,528));
        Fadein->start();
    });
}
