#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QSettings>
#include <QStandardPaths>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chinaMapWidget = new ChinaMapWidget(this);
    avatarLabel = new QLabel("Avatar", this);
    avatarLabel->setFixedSize(100, 100); // 设置头像标签的固定大小
    avatarLabel->setAlignment(Qt::AlignCenter); // 添加边框以示预留空间
    QString path="D:/qtfile/mapproject/bin/微信图片_20240601162017.png";
    QPixmap pixmap(path);
    avatarLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    QLabel* idTitleLabel = new QLabel("ID:", this);
    IDLabel = new QLabel("ID", this);
    QLabel* nicknameTitleLabel = new QLabel("Nickname:", this);
    nicknameLabel = new QLabel("Nickname", this);

    changeAvatarButton = new QPushButton("Change Avatar", this);
    updateNicknameButton = new QPushButton("Update Nickname", this);
    updateIdButton = new QPushButton("Login(Use your id)", this);

    connect(changeAvatarButton, &QPushButton::clicked, this, &MainWindow::changeAvatarClicked);
    connect(updateNicknameButton, &QPushButton::clicked, this, &MainWindow::updateNicknameClicked);
    connect(updateIdButton, &QPushButton::clicked, this, &MainWindow::updateIdClicked);

    QVBoxLayout* userInfoLayout = new QVBoxLayout;
    userInfoLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);
    userInfoLayout->addWidget(changeAvatarButton);

    QHBoxLayout* idLayout = new QHBoxLayout;
    idLayout->addWidget(idTitleLabel);
    idLayout->addWidget(IDLabel);
    userInfoLayout->addLayout(idLayout);

    QHBoxLayout* nicknameLayout = new QHBoxLayout;
    nicknameLayout->addWidget(nicknameTitleLabel);
    nicknameLayout->addWidget(nicknameLabel);
    userInfoLayout->addLayout(nicknameLayout);

    userInfoLayout->addWidget(updateIdButton);
    userInfoLayout->addWidget(updateNicknameButton);
    userInfoLayout->addStretch();

    userInfoWidget = new QWidget(this);
    userInfoWidget->setLayout(userInfoLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(chinaMapWidget,3);
    mainLayout->addWidget(userInfoWidget,1);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    chinaMapWidget->loadJson(QApplication::applicationDirPath() + "/datas.json");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeAvatarClicked()
{
    if (IDLabel->text() == "ID") {
        QMessageBox::warning(this, "Please Login", "Please login before changing avatar.");
        return;
    }
    QString avatarPath = QFileDialog::getOpenFileName(this, "Select Avatar", "", "Images (*.png *.jpg *.bmp)");
    if (!avatarPath.isEmpty()) {
        QPixmap pixmap(avatarPath);
        avatarLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
        saveUserInfo(IDLabel->text(), "AvatarPath", avatarPath);
    }
}

void MainWindow::updateNicknameClicked()
{
    if (IDLabel->text() == "ID") {
        QMessageBox::warning(this, "Please Login", "Please login before updating nickname.");
        return;
    }

    bool ok;
    QString nickname = QInputDialog::getText(this, tr("Update Nickname"),
                                             tr("Nickname:"), QLineEdit::Normal,
                                             nicknameLabel->text(), &ok);

    if (!ok || nickname.isEmpty()) return;
    if (ok && !nickname.isEmpty()) {
        nicknameLabel->setText(nickname);
        saveUserInfo(IDLabel->text(), "Nickname", nickname);
    }
}

void MainWindow::updateIdClicked(){
    bool ok;
    QString newID = QInputDialog::getText(this, tr("Login(Use your id)"),
                                          tr("ID:"), QLineEdit::Normal,
                                          IDLabel->text(), &ok);
    chinaMapWidget->ID=newID;
    if (!ok || newID.isEmpty()) {
        return; }

    QString savedNickname = loadUserInfo(newID, "Nickname");
    QString savedAvatarPath = loadUserInfo(newID, "AvatarPath");

    if (!savedNickname.isEmpty() && !savedAvatarPath.isEmpty()) {
        // 如果本地数据库中存在该ID的昵称和头像信息，则自动加载
        nicknameLabel->setText(savedNickname);
        QPixmap pixmap(savedAvatarPath);
        avatarLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    }
    else{
        nicknameLabel->setText("Nickname");
        QString path="D:/qtfile/mapproject/bin/微信图片_20240601162017.png";
        QPixmap pixmap(path);
        avatarLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    }

    IDLabel->setText(newID);
    saveUserInfo(newID, "ID", newID);
}
void MainWindow::saveUserInfo(const QString& id, const QString& key, const QString& value)
{
    QSettings settings(QApplication::applicationDirPath() + "/userinfo.ini", QSettings::IniFormat);
    settings.beginGroup(id);
    settings.setValue(key, value);
    settings.endGroup();
}

QString MainWindow::loadUserInfo(const QString& id, const QString& key)
{
    QSettings settings(QApplication::applicationDirPath() + "/userinfo.ini", QSettings::IniFormat);
    settings.beginGroup(id);
    QString value = settings.value(key).toString();
    settings.endGroup();
    return value;
}
