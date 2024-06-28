#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chinamapwidget.h"
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    ChinaMapWidget* chinaMapWidget;

private slots:
    void changeAvatarClicked();
    void updateNicknameClicked();
    void updateIdClicked();
    void saveUserInfo(const QString& id, const QString& key, const QString& value);
    QString loadUserInfo(const QString& id, const QString& key);

private:
    Ui::MainWindow* ui;
    QLabel* avatarLabel;
    QLabel* nicknameLabel;
    QLabel* IDLabel;
    QPushButton* changeAvatarButton;
    QPushButton* updateNicknameButton;
    QPushButton* updateIdButton;
    QWidget* userInfoWidget;
};

#endif // MAINWINDOW_H
