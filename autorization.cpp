#include "autorization.h"
#include "ui_autorization.h"
#include "mainwindow.h"
#include "mainshop.h"
#include <QMessageBox>
#include <QSettings>
#include <QIcon>
#include <QAction>
#include <QLineEdit>
#include <QPixmap>
#include <QPainter>
#include <QStyle>
#include <QPaintDevice>
#include <fstream>
#include "json.hpp"
#include <QCryptographicHash>
#include <QDebug>
#include "ErrorHandler.h"


using json = nlohmann::json;

autorization::autorization(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::autorization)
{
    ui->setupUi(this);

    SetIconsFA();

    ui->password->setEchoMode(QLineEdit::Password);

    connect(ui->checkBoxpassword, SIGNAL(stateChanged(int)), this, SLOT(on_checkBoxpassword_stateChanged(int)));

    this->setWindowTitle("Oriventa Shop");
    QIcon icon(":/images/OS.PNG");
    this->setWindowIcon(icon);

    this->setFixedSize(800,600);

    QSettings settings("MyApp", "MyShop");
    if (settings.value("rememberMe", false).toBool()) {
        ui->login->setText(settings.value("login", "").toString());
        ui->password->setText(settings.value("password", "").toString());
        ui->checkBoxremember->setChecked(true);
    } else {
        ui->checkBoxremember->setChecked(false);
        settings.clear();
    }
}

autorization::~autorization()
{
    delete ui;
}

void autorization::on_pushButton_3_clicked()
{
    MainWindow* window = new MainWindow;
    this->close();
    window->show();
}


void autorization::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();


    if (login.isEmpty()) {
        ErrorHandler::showWarning(this, "Помилка!", "Логін не може бути порожнім!");
        ui->login->setStyleSheet("border: 1px solid red;");
        return;
    } else {
        ui->login->setStyleSheet("border: 1px solid green;");
    }

    if (password.isEmpty()) {
        ErrorHandler::showWarning(this, "Помилка!", "Пароль не може бути порожнім!");
        ui->password->setStyleSheet("border: 1px solid red;");
        return;
    } else {
        ui->password->setStyleSheet("border: 1px solid green;");
    }



    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();


    const std::string filePath = "users.json";
    json allUsers;

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        ErrorHandler::showCritical(this, "Помилка!", "Не вдалося відкрити файл користувачів!");
        ErrorHandler::logError("Помилка: не вдалося відкрити файл users.json");
        return;
    }


    try {
        inputFile >> allUsers;
    } catch (const nlohmann::json::parse_error& e) {
        ErrorHandler::logError("Помилка парсингу JSON: " + QString(e.what()));
        ErrorHandler::showCritical(this, "Помилка!", "Файл користувачів пошкоджений!");
        inputFile.close();
        return;
    }

    inputFile.close();

    bool loginSuccessful = false;


    for (const auto& user : allUsers) {
        QString userLogin;
        QString userPassword;


        if (user.contains("login") && user.contains("password")) {

            if (user["login"].is_string()) {
                userLogin = QString::fromStdString(user["login"]);
            } else if (user["login"].is_number()) {
                userLogin = QString::number(user["login"].get<int>());
            } else {
                ErrorHandler::logError("Непідтримуваний тип даних для логіну");
                continue;
            }

            if (user["password"].is_string()) {
                userPassword = QString::fromStdString(user["password"]);
            } else {
                 ErrorHandler::logError("Непідтримуваний тип даних для пароля");
                continue;
            }


            if (userLogin == login && userPassword == hashedPassword) {
                loginSuccessful = true;
                break;
            }
        } else {
            qDebug() << "Отсутствуют ключи 'login' или 'password' в JSON";
        }
    }


    if (loginSuccessful) {

        if (ui->checkBoxremember->isChecked()) {
            QSettings settings("MyApp", "MyShop");
            settings.setValue("login", login);
            settings.setValue("password", password);
            settings.setValue("rememberMe", true);
        } else {
            QSettings settings("MyApp", "MyShop");
            settings.remove("login");
            settings.remove("password");
            settings.setValue("rememberMe", false);
        }

        QMessageBox::information(this, "Успіх", "😊 Ласкаво просимо " + login + "!");
        mainshop* window = new mainshop(login);
        this->close();
        window->showMaximized();
    } else {
        ErrorHandler::showWarning(this, "Помилка!", "Неправильний логін або пароль!");
        ui->login->setStyleSheet("border: 1px solid red;");
        ui->password->setStyleSheet("border: 1px solid red;");
    }
}



void autorization::SetIconsFA() {
    QLineEdit *loginEdit = findChild<QLineEdit*>("login");

    if (loginEdit) {

        QString emoji = "👤";

        QPixmap pixmap(16, 16);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        painter.drawText(pixmap.rect(), Qt::AlignCenter, emoji);

        QIcon icon(pixmap);

        loginEdit->addAction(icon, QLineEdit::LeadingPosition);
    }

    QLineEdit *password = findChild<QLineEdit*>("password");

    if (password) {

        QString emoji = "🔒";

        QPixmap pixmap(16,16);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        painter.drawText(pixmap.rect(), Qt::AlignCenter, emoji);

        QIcon icon(pixmap);

        password->addAction(icon, QLineEdit::LeadingPosition);
    }

    QString unicodeArrow = "←";
    QPixmap pixmap(41, 41);
    pixmap.fill(Qt::transparent);


    QPainter painter(&pixmap);
    QFont font = painter.font();
    font.setPointSize(30);
    painter.setFont(font);
    painter.setPen(Qt::white);
    QRect adjustedRect = pixmap.rect().adjusted(0, -10, 0, 0);
    painter.drawText(adjustedRect, Qt::AlignCenter, unicodeArrow);
    painter.end();


    QIcon arrowIcon(pixmap);
    ui->pushButton_3->setIcon(arrowIcon);
    ui->pushButton_3->setIconSize(QSize(41, 41));
    ui->pushButton_3->setText("");
}


void autorization::on_checkBoxpassword_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked) {
        ui->password->setEchoMode(QLineEdit::Normal);
    } else {
        ui->password->setEchoMode(QLineEdit::Password);
    }
}

