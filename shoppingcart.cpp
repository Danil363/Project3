#include "shoppingcart.h"
#include "ui_shoppingcart.h"
#include <QMessageBox>
#include <fstream>
#include "json.hpp"
#include <QDebug>
#include "errorhandler.h"

using json = nlohmann::json;




shoppingcart::shoppingcart(QWidget *parent)
    : QDialog(parent), ui(new Ui::shoppingcart)
{
    ui->setupUi(this);
    this->setFixedSize(600, 500);


}

shoppingcart::shoppingcart(const QList<Product>& products, const QString& login, QWidget *parent)
    : QDialog(parent), ui(new Ui::shoppingcart)
{
    ui->setupUi(this);
    this->setFixedSize(600, 500);


    currentUserLogin = login;

    loadUserBalance();


    for (const Product& product : products) {
        addProductToCart(product);
    }
}

void shoppingcart::loadUserBalance() {
    const std::string filePath = "users.json";
    nlohmann::json allUsers;

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        ErrorHandler::logError("Не вдалося відкрити файл користувачів!");
        return;
    }

    try {
        inputFile >> allUsers;
    } catch (const nlohmann::json::parse_error& e) {
        ErrorHandler::logError("Помилка парсингу JSON");
        return;
    }
    inputFile.close();


    auto it = std::find_if(allUsers.begin(), allUsers.end(), [&](const nlohmann::json& user) {
        return user["login"] == currentUserLogin.toStdString();
    });

    if (it != allUsers.end()) {
        userBalance = (*it)["balance"];
    } else {
        ErrorHandler::logError("Користувач з логіном" + currentUserLogin + "не знайден!");
    }
}


void shoppingcart::updateUserBalanceInJson() {
    const std::string filePath = "users.json";
    nlohmann::json allUsers;


    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        ErrorHandler::logError("Не вдалося відкрити файл для оновлення балансу!");
        return;
    }

    try {
        inputFile >> allUsers;
    } catch (const nlohmann::json::parse_error& e) {
        ErrorHandler::logError("Помилка парсингу JSON:");
        return;
    }
    inputFile.close();


    for (auto& user : allUsers) {
        if (user["login"] == currentUserLogin.toStdString()) {
            user["balance"] = userBalance;
            break;
        }
    }

    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        ErrorHandler::logError("Не вдалося відкрити файл для запису оновленого балансу!");
        return;
    }

    outputFile << allUsers.dump(4);
    outputFile.close();
}

shoppingcart::~shoppingcart()
{
    delete ui;
}

void shoppingcart::addProductToCart(const Product& product) {
    cartProducts.append(product);

    QListWidgetItem* item = new QListWidgetItem(product.name + " | Кількість: 1 | Ціна: " + QString::number(product.price, 'f', 2) + " грн");

    item->setTextAlignment(Qt::AlignHCenter);
    ui->ItemsInCart->setSpacing(2);

    ui->ItemsInCart->addItem(item);


    totalCost += product.price;
    totalCount += 1;

    updateSummary();
}


void shoppingcart::updateSummary() {
    ui->cost->setText(QString::number(totalCost, 'f', 2) + " грн");
    ui->count->setText(QString::number(totalCount));
}

void shoppingcart::logPurchaseToCsv(const QString& details, double total, double balanceAfterPurchase) {
    const std::string filePath = "purchase_logs.csv";

    std::ofstream csvFile(filePath, std::ios::app);
    if (!csvFile.is_open()) {
        ErrorHandler::logError("Не вдалося відкрити файл для запису логів покупок!");
        return;
    }

    try {

        static bool firstRun = true;
        if (firstRun) {
            std::ifstream checkFile(filePath);
            if (checkFile.peek() == std::ifstream::traits_type::eof()) {
                csvFile << "Покупка;Сума (грн);Баланс після покупки (грн)" << std::endl;
            }
            firstRun = false;
        }


        csvFile << details.toStdString() << ";"
                << total << ";"
                << balanceAfterPurchase
                << std::endl;

    } catch (const std::exception& e) {
        ErrorHandler::logError("Ошибка записи в CSV файл");
    }

    csvFile.close();
}

void shoppingcart::on_pushButton_2_clicked()
{
    if (cartProducts.isEmpty()) {
        ErrorHandler::showWarning(this, "Помилка", "Корзина порожня! Додайте товари перед покупкою.");
        return;
    }

    QString details;
    double total = 0.0;

    for (const Product& product : cartProducts) {
        details += product.name + " | Ціна: " + QString::number(product.price, 'f', 2) + " грн\n";
        total += product.price;
    }

    if (total > userBalance) {
        ErrorHandler::showWarning(this, "Помилка", "Недостатньо коштів на балансі для здійснення покупки!");
        return;
    }


    userBalance -= total;
    updateUserBalanceInJson();

    details += "\nЗагальна сума: " + QString::number(total, 'f', 2) + " грн";
    details += "\nВаш поточний баланс: " + QString::number(userBalance, 'f', 2) + " грн";
    ErrorHandler::showInfo(this, "Дякуємо за покупку!", "Ваше замовлення:\n" + details);


    logPurchaseToCsv(details, total, userBalance);

    ui->ItemsInCart->clear();
    cartProducts.clear();
    totalCost = 0.0;
    totalCount = 0;
    updateSummary();
}





void shoppingcart::on_pushButton_clicked()
{
    QListWidgetItem* currentItem = ui->ItemsInCart->currentItem();

    if (currentItem) {
        int row = ui->ItemsInCart->row(currentItem);


        totalCost -= cartProducts[row].price;
        totalCount--;
        cartProducts.removeAt(row);

        delete ui->ItemsInCart->takeItem(row);

        updateSummary();
    }
}



double shoppingcart::extractPriceFromItem(const QString& itemText) {
    QStringList parts = itemText.split('|');
    if (parts.size() >= 2) {
        QString priceText = parts[2].trimmed();
        priceText = priceText.remove("Ціна: ").remove(" грн");
        return priceText.toDouble();
    }
    return 0.0;
}

