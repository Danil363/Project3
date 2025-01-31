#include "registration.h"
#include "ui_registration.h"
#include "mainwindow.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QIcon>
#include <QAction>
#include <QLineEdit>
#include <QPixmap>
#include <QPainter>
#include "json.hpp"
#include <fstream>
#include <QDir>
#include <QCryptographicHash>
#include "errorhandler.h"

using json = nlohmann::json;

registration::registration(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::registration)
{
    ui->setupUi(this);

    SetIconsFR();

    this->setFixedSize(800,600);

    this->setWindowTitle("Oriventa Shop");
    QIcon icon(":/images/OS.PNG");
    this->setWindowIcon(icon);
}

registration::~registration()
{
    delete ui;
}

void registration::on_pushButton_2_clicked()
{
    MainWindow* window = new MainWindow(this);
    this->close();
    window->show();
}


void registration::on_pushButton_clicked()
{

    QString login = ui->login->text();
    QString password = ui->password->text();
    QString password_conf = ui->password_conf->text();

    static QRegularExpression loginRegex("^[a-zA-Z0-9]+$");
    QRegularExpressionMatch match = loginRegex.match(login);
    if (!match.hasMatch()) {
        ui->login->setStyleSheet("border: 1px solid red;");
        ErrorHandler::showWarning(this, "Помилка!", "В логіні можна використовувати тільки англійські літери та символи!");
        return;
    } else {
        ui->login->setStyleSheet("border: 1px solid green;");
        ui->password->setStyleSheet("border: 1px solid green;");
        ui->password_conf->setStyleSheet("border: 1px solid green;");
    }

    if (password.length() < 8) {
        ui->password->setStyleSheet("border: 1px solid red;");
        ui->password_conf->setStyleSheet("border: 1px solid red;");
        ErrorHandler::showWarning(this, "Помилка!", "Пароль має містити мінімум 8 символів!");
        return;
    } else {
        ui->password->setStyleSheet("border: 1px solid green;");
    }

    if (password != password_conf) {
        ui->password_conf->setStyleSheet("border: 1px solid red;");
        ErrorHandler::showWarning(this, "Помилка!", "Введені паролі не співвпадають!");
        return;
    } else {
        ui->password_conf->setStyleSheet("border: 1px solid green;");
    }

     QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    json userData;
    userData["login"] = login.toStdString();
    userData["password"] = hashedPassword.toStdString();
    userData["balance"]=5000;
    userData["isAdmin"]=false;


    const std::string filePath = "users.json";
    json allUsers;

    std::ifstream inputFile(filePath);
    if (inputFile.is_open()) {
        try {
            inputFile >> allUsers;
            ErrorHandler::logError("Файл успішно прочитано.");
        } catch (const json::parse_error& e) {
            ErrorHandler::logError("Помилка парсинга JSON");
            allUsers = json::array();
        }
        inputFile.close();
    } else {
        ErrorHandler::logError("Файл не найден. Создается новый JSON.");
        allUsers = json::array();
    }


    if (!allUsers.is_array()) {
        ErrorHandler::logError("Дані у файлі є масивом. Створюється новий масив.");
        allUsers = json::array();
    }

    for (const auto& user : allUsers) {
        if (user["login"] == login.toStdString()) {
            ErrorHandler::showWarning(this, "Помилка!", "Логін вже зайнятий!");
            return;
        }
    }

    if (password == "admin228") {
        userData["isAdmin"] = true;
    } else {
        userData["isAdmin"] = false;
    }


    allUsers.push_back(userData);
    ErrorHandler::logError("Доданий новий користувач:" + QString::fromStdString(userData.dump()));

    std::ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << allUsers.dump(4);
        outputFile.close();
        ErrorHandler::logError("Дані успішно записані у файл.");
    } else {
        ErrorHandler::showCritical(this, "Помилка!", "Неможливо записати дані у файл users.json!");
        ErrorHandler::logError("Помилка при відкритті файлу для запису.");
        return;
    }

    ErrorHandler::showInfo(this, "Успіх!", "Ви успішно зареєструвалися!");
    MainWindow *window = new MainWindow(this);
    this->close();
    window->show();
}

void registration::SetIconsFR() {
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

    QLineEdit *password_conf = findChild<QLineEdit*>("password_conf");

    if (password_conf) {

        QString emoji = "🔒";

        QPixmap pixmap(16,16);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        painter.drawText(pixmap.rect(), Qt::AlignCenter, emoji);

        QIcon icon(pixmap);

        password_conf->addAction(icon, QLineEdit::LeadingPosition);
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
    ui->pushButton_2->setIcon(arrowIcon);
    ui->pushButton_2->setIconSize(QSize(41, 41));
    ui->pushButton_2->setText("");
}



