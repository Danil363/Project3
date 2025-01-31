#include "addproductdialog.h"
#include "ui_addproductdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QAbstractItemView>
#include "json.hpp"
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "ErrorHandler.h"

using json = nlohmann::json;


addproductdialog::addproductdialog(const QStringList &categories, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addproductdialog)
    , categories(categories)
{
    ui->setupUi(this);
    this->setFixedSize(600,400);
    ui->comboBox->addItems(categories);


    connect(ui->addphoto, &QPushButton::clicked, this, &addproductdialog::onSelectPhoto);
    connect(ui->confirm, &QPushButton::clicked, this, &addproductdialog::onAddProduct);
    connect(ui->cancel, &QPushButton::clicked, this, &addproductdialog::reject);

    QString cart = "🖼️";
    QPixmap pixmap1(64, 64);
    pixmap1.fill(Qt::transparent);

    QPainter painter(&pixmap1);
    QFont font = painter.font();
    font.setPointSize(20);
    painter.setFont(font);
    painter.setPen(Qt::black);
    QRect adjustedRect = pixmap1.rect().adjusted(0, 0, 0, 0);
    painter.drawText(adjustedRect, Qt::AlignCenter, cart);
    painter.end();
    QIcon cartIcon(pixmap1);
    ui->addphoto->setIcon(cartIcon);
    ui->addphoto->setIconSize(QSize(64, 64));
    ui->addphoto->setText("");

    ui->comboBox->view()->setFocusPolicy(Qt::NoFocus);

    ui->comboBox->setStyleSheet(
        "QComboBox {"
        "    border: 2px solid #cccccc;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    background-color: white;"
        "    color: black;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "    border: 2px solid #cccccc;"
        "    background-color: white;"
        "    border-radius: 5px;"
        "    outline: none;"
        "}"
        "QComboBox QAbstractItemView::item {"
        "    background: transparent;"
        "    background-color: rgb(87, 0, 134);"
        "    color: white;"
        "    padding: 5px;"
        "    margin: 2px;"
        "    border-radius: 5px;"
        "    outline: none;"
        "}"
        "QComboBox QAbstractItemView::item:hover {"
        "    background-color: #e6f7ff;"
        "    border: 1px solid #87ceeb;"
        "    color: #005f8a;"
        "    outline: none;"
        "}"
        );

}


addproductdialog::~addproductdialog()
{
    delete ui;
}

void addproductdialog::onSelectPhoto()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Виберіть фото", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!filePath.isEmpty()) {
        selectedPhotoPath = filePath;
    }
}



void addproductdialog::onAddProduct()
{
    QString name = ui->name->text();
    double price = ui->price->text().toDouble();
    QString category = ui->comboBox->currentText();

    if (name.isEmpty()) {
        ErrorHandler::showWarning(this, "Помилка", "Введіть назву товару!");
        return;
    }

    if (selectedPhotoPath.isEmpty()) {
        ErrorHandler::showWarning(this, "Помилка", "Виберіть фото!");
        return;
    }

    if (price <= 0.0) {
        ErrorHandler::showWarning(this, "Помилка", "Ціна повинна бути вище 0!");
        return;
    }

    if (category.isEmpty()) {
        ErrorHandler::showWarning(this, "Помилка", "Виберіть категорію!");
        return;
    }


    nlohmann::json newProduct;
    newProduct["name"] = name.toStdString();
    newProduct["path"] = selectedPhotoPath.toStdString();
    newProduct["price"] = price;

    if (category == "Продукты") {
        QString expirationDate = "";
        newProduct["expirationDate"] = expirationDate.toStdString();
    } else if (category == "Побутова техніка") {
        QString warranty = "";
        newProduct["warranty"] = warranty.toStdString();
    } else if (category == "Зоотовари") {
        QString animalType = "";
        newProduct["animalType"] = animalType.toStdString();
    } else if (category == "Одяг") {
        QString material = "";
        QString size = "";
        newProduct["material"] = material.toStdString();
        newProduct["size"] = size.toStdString();
    } else if (category == "Сантехніка") {
        QString material = "";
        newProduct["material"] = material.toStdString();
    } else if (category == "Товари для дому") {
        double weight = 0.0;
        QString size = "";
        newProduct["weight"] = weight;
        newProduct["size"] = size.toStdString();
    } else if (category == "Електроніка") {
        QString operatingTime  = "";
        QString size = "";
        newProduct["operatingTime"] = operatingTime.toStdString();
    }



    const std::string filePath = "data.json";
    QString absolutePath = QDir::current().absoluteFilePath(QString::fromStdString(filePath));
    nlohmann::json data;

    std::ifstream inputFile(filePath);
    if (inputFile.is_open()) {
        try {
            inputFile >> data;
        } catch (const nlohmann::json::parse_error &e) {
            ErrorHandler::logError("Помилка парсинга JSON: " + QString(e.what()));
            ErrorHandler::showCritical(this, "Помилка", "Файл даних пошкоджено. Не можна додати товар.");
            return;
        }
        inputFile.close();
    } else {
        ErrorHandler::logError("Файл не знайдено. Створюється новий JSON.");
        ErrorHandler::showCritical(this, "Помилка", "Файл категорій не знайдено!");
        return;
    }


    if (!data.contains(category.toStdString())) {
        ErrorHandler::showCritical(this, "Помилка", "Вибраної категорії не існує!");
        return;
    }


    if (!data[category.toStdString()].is_array()) {
        ErrorHandler::showCritical(this, "Помилка", "Неправильний формат даних для категорії!");
        return;
    }


    data[category.toStdString()].push_back(newProduct);



    std::ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << data.dump(4);
        outputFile.close();
    } else {
        ErrorHandler::showCritical(this, "Помилка!", "Не вдалося записати данні у файл data.json!");
        ErrorHandler::logError("Помилка при відкритті файла для запису.");
        return;
    }

    emit productAdded(name, price, selectedPhotoPath, category);
    QMessageBox::information(this, "Успіх", "Товар успішно додано!");
    accept();
}

