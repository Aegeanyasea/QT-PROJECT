#ifndef TRAVEL_ON_LINE_H
#define TRAVEL_ON_LINE_H

#include <QWidget>
#include<QPushButton>
#include<QStringList>
#include<QLabel>
#include<QFile>
#include<QTimer>
#include<QPropertyAnimation>
#include<QTextEdit>
#include<QDir>
#include<QWebEngineView>

namespace Ui {
class travel_on_line;
}

class travel_on_line : public QWidget
{
    Q_OBJECT

public:
    explicit travel_on_line(QWidget *parent = nullptr,QString name="a");
    ~travel_on_line();

private slots:
    void on_pushButton_clicked();
    void showNextImage();

private:
    Ui::travel_on_line *ui;
    QString provinceName;
    QPushButton* pic;
    QStringList introduction;
    QStringList image;
    QLabel* ima;
    QTimer* time;
    int num=0;
    int now=0;
    QWebEngineView *webView;

    QPropertyAnimation* Fadein;
    QPropertyAnimation* Fadeout;

    void setupanimation();

};

#endif // TRAVEL_ON_LINE_H
