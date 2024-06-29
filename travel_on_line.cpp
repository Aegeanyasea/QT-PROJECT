#include "travel_on_line.h"
#include "ui_travel_on_line.h"
#include<QTimer>
#include<QPropertyAnimation>
#include<QGraphicsOpacityEffect>
#include<QDir>
#include<QWebEngineView>

travel_on_line::travel_on_line(QWidget *parent,QString name)
    : QWidget(parent)
    , ui(new Ui::travel_on_line)
{
    ui->setupUi(this);
    provinceName=name;
    pic=new QPushButton("GO",this);
    ima=new QLabel(this);
    setWindowTitle("云游"+provinceName);
    ima->setFixedSize(400, 528); // 设置头像标签的固定大小
    ima->setAlignment(Qt::AlignCenter); // 添加边框以示预留空间

    QString filePath=QApplication::applicationDirPath()+"/"+this->provinceName+"pictureshow0"+".txt";
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        in>>num;
        in.readLine();
        while(!in.atEnd()){
            image.append(in.readLine());
        }
        file.close();
    }

    pic->setText("GO!");
    pic->move(140,530);
    resize(400,550);
    connect(pic,&QPushButton::clicked,this,&travel_on_line::on_pushButton_clicked);

    time=new QTimer(this);
    connect(time,&QTimer::timeout,this,&travel_on_line::showNextImage);
    time->start(10000);
    setupanimation();
    showNextImage();
}

travel_on_line::~travel_on_line()
{
    delete ui;
}

void travel_on_line::on_pushButton_clicked()
{
    showNextImage();
    // 创建并显示 QWebEngineView 窗口
    webView = new QWebEngineView();
    webView->setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭时自动删除
    webView->resize(1200, 800); // 设置窗口大小为1200x800像素
    webView->load(QUrl::fromLocalFile(QDir::currentPath() + "/../博客/index.html"));
    webView->show();
}

void travel_on_line::setupanimation(){
    QGraphicsOpacityEffect *effect=new QGraphicsOpacityEffect(this);
    ima->setGraphicsEffect(effect);

    Fadeout =new QPropertyAnimation(effect,"opacity");
    Fadeout->setDuration(2000);
    Fadeout->setStartValue(1.0);
    Fadeout->setEndValue(0.0);

    Fadein=new QPropertyAnimation(effect,"opacity");
    Fadein->setDuration(2000);
    Fadein->setStartValue(0.0);
    Fadein->setEndValue(1.0);

    connect(Fadeout,&QPropertyAnimation::finished,[this]{
        QString filename=image.at(now);
        QImage imageshow=QImage(filename);
        ima->setPixmap(QPixmap::fromImage(imageshow).scaled(400,528));
        Fadein->start();
    });
}

void travel_on_line::showNextImage(){
    if(num==0){
        return;
    }
    QString filename=image.at(now);
    now++;
    now=now%num;
    QImage imageshow=QImage(filename);
    ima->setPixmap(QPixmap::fromImage(imageshow).scaled(400,528));
    Fadeout->start();
}