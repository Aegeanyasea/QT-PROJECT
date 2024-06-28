#ifndef PROVINCEINFODIALOG_H
#define PROVINCEINFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <provincerec.h>
#include <QStringList>
#include<QPropertyAnimation>
#include<QTimer>

class ProvinceInfoDialog : public QDialog {
    Q_OBJECT

public:
    ProvinceInfoDialog(QWidget* parent = nullptr);
    void setProvinceInfo(const QString& provinceName, const QString& provinceInfo,QString ID0);
    //void loadTextFromFile(const QString& filePath);

private slots:
    void saveButtonClicked();
    void imageButtonClicked();
    void changeButtonClicked();

private:
    QLabel* nameLabel;
    QPlainTextEdit* infoTextEdit;
    QPushButton* saveButton;
    QPushButton* imageButton;
    QLabel* image;
    QString provincename;
    QStringList imageName;
    QPushButton* changeButton;
    int num=0;
    int now=0;
    QString ID;
    QTimer *time;

    QPropertyAnimation* Fadein;
    QPropertyAnimation* Fadeout;
    void setupanimation();
};

#endif // PROVINCEINFODIALOG_H
