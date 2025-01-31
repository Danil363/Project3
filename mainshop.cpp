#include "mainshop.h"
#include "clothing.h"
#include "electronic.h"
#include "homeappliance.h"
#include "homegood.h"
#include "petsupply.h"
#include "plumbing.h"
#include "ui_mainshop.h"
#include "mainwindow.h"
#include "shoppingcart.h"
#include "addproductdialog.h"
#include "json.hpp"
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QPixmap>
#include <QScrollArea>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QStyleOptionButton>
#include <QSpacerItem>
#include <algorithm>
#include <random>
#include <fstream>
#include <QList>
#include <QString>
#include <QMap>
#include <QSet>
#include "product.h"
#include "food.h"
#include "errorhandler.h"


mainshop::mainshop(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainshop)
{
    ui->setupUi(this);
}

mainshop::mainshop(const QString &login, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainshop)
{
    ui->setupUi(this);

    ui->categoryList->setCurrentRow(0);
    ui->categoryList->item(0)->setSelected(true);

    this->setWindowTitle("Oriventa Shop");
    QIcon icon(":/images/OS.PNG");
    this->setWindowIcon(icon);

    const std::string filePath = "users.json";
    bool isAdmin = isUserAdmin(login, filePath);

    ui->Button_user->setText(login);

    SetIconsFS();
    Catalog();
    loadCategoriesFromJson("data.json");


    cart = new shoppingcart(QList<Product>(), login, this);
    cart->setWindowTitle("Корзина");
    connect(this, &mainshop::productAddedToCart, cart, &shoppingcart::addProductToCart);
    connect(ui->search, &QLineEdit::textChanged, this, &mainshop::searchProducts);

    connect(ui->sort2, &QPushButton::clicked, this, &mainshop::sortProductsAscending);
    connect(ui->sort1, &QPushButton::clicked, this, &mainshop::sortProductsDescending);
    connect(ui->resetButton, &QPushButton::clicked, this, &mainshop::resetSorting);





    QMenu *menu = new QMenu(this);

    QAction *logoutAction = new QAction("Вийти", this);
    menu->addAction(logoutAction);

    QAction *addItemsAction = new QAction("Додати товар", this);
    if (isAdmin) {
        menu->addAction(addItemsAction);
    }

    menu->setStyleSheet(
        "QMenu {"
        "   background-color: white;"
        "   border: 1px solid #c0c0c0;"
        "   padding: 5px;"
        "}"
        "QMenu::item {"
        "   padding: 6px 12px;"
        "   color: black;"
        "   border-radius: 5px;"
        "}"
        "QMenu::item:selected {"
        "   background-color: rgb(87, 0, 134);"
        "   color: white;"
        "   border-radius: 5px;"
        "}"
        );

    ui->Button_user->setMenu(menu);

    connect(logoutAction, &QAction::triggered, this, &mainshop::logout);
    connect(addItemsAction, &QAction::triggered, this, &mainshop::onAddItems);
    connect(ui->categoryList, &QListWidget::itemClicked, this, &mainshop::onCategorySelected);



    QGridLayout* layout = new QGridLayout();
    layout->setSpacing(40);
    layout->setAlignment(Qt::AlignTop);

    QWidget* scrollContent = new QWidget();
    scrollContent->setLayout(layout);
    ui->scrollArea->setWidget(scrollContent);
    ui->scrollArea->setWidgetResizable(true);

    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "   background-color: white;"
        "   border: none;"
        "   padding: 10px;"
        "   border-radius: 10px;"
        "}"
        );

    this->gridLayout = layout;

    displayProductsForCategory("Головна сторінка");
}

mainshop::~mainshop()
{
    delete ui;
}

void mainshop::Catalog() {
    ui->categoryList->setSpacing(2);
}

void mainshop::SetIconsFS()
{
    QLineEdit *searchEdit = findChild<QLineEdit*>("search");

    if (searchEdit) {
        QString searchIcon = "🔍";
        QPixmap searchPixmap(16, 16);
        searchPixmap.fill(Qt::transparent);

        QPainter searchPainter(&searchPixmap);
        searchPainter.drawText(searchPixmap.rect(), Qt::AlignCenter, searchIcon);

        QIcon searchIconFinal(searchPixmap);
        searchEdit->addAction(searchIconFinal, QLineEdit::LeadingPosition);

        QString clearIcon = "⨉";
        QPixmap clearPixmap(16, 16);
        clearPixmap.fill(Qt::transparent);

        QPainter clearPainter(&clearPixmap);
        clearPainter.drawText(clearPixmap.rect(), Qt::AlignCenter, clearIcon);

        QAction *clearAction = new QAction(QIcon(clearPixmap), "", searchEdit);
        searchEdit->addAction(clearAction, QLineEdit::TrailingPosition);
        clearAction->setVisible(false);

        connect(searchEdit, &QLineEdit::textChanged, this, [=](const QString &text) {
            clearAction->setVisible(!text.isEmpty());
        });

        connect(clearAction, &QAction::triggered, this, [=]() {
            searchEdit->clear();
        });
    }

    QPixmap pixmap(":/images/OS.PNG");

    ui->Logos->setPixmap(pixmap);
    ui->Logos->setScaledContents(true);

    QString cart = "🛒";
    QPixmap pixmap1(52, 52);
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
    ui->cart->setIcon(cartIcon);
    ui->cart->setIconSize(QSize(52, 52));
    ui->cart->setText("");
}


void mainshop::logout()
{
    MainWindow* window = new MainWindow;
    this->close();
    window->show();
}

void mainshop::on_cart_clicked()
{
    cart->show();
    cart->raise();
    cart->activateWindow();
}



void mainshop::addProductCard(const Product& product) {

    QWidget* cardWidget = new QWidget();
    cardWidget->setFixedSize(200, 300);


    cardWidget->setStyleSheet(
        "QWidget {"
        "    background-color: white;"
        "    border: 1px solid #dcdcdc;"
        "    border-radius: 10px;"
        "}"
        );

    QVBoxLayout* cardLayout = new QVBoxLayout(cardWidget);
    cardLayout->setAlignment(Qt::AlignCenter);

    QLabel* imageLabel = new QLabel();
    imageLabel->setFixedSize(180, 180);
    imageLabel->setPixmap(QPixmap(product.imagePath).scaled(180, 180, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("border-radius: 10px; border-top: none; ");


    QLabel* nameLabel = new QLabel(product.name);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #333333; border: none;");

    QLabel* priceLabel = new QLabel(QString::number(product.price, 'f', 2) + " грн");
    priceLabel->setAlignment(Qt::AlignCenter);
    priceLabel->setStyleSheet("color: #ff6600; font-size: 16px; font-weight: bold; border: none;");


    QPushButton* buyButton = new QPushButton("Купити");
    buyButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgb(87, 0, 134);"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgb(0, 238, 255);"
        "}"
        );
    connect(buyButton, &QPushButton::clicked, this, [this, product]() {
        emit productAddedToCart(product);
        ErrorHandler::showInfo(this, "Додано до корзини", product.name + " успішно додано!");
    });



    cardLayout->addWidget(imageLabel);
    cardLayout->addWidget(nameLabel);
    cardLayout->addWidget(priceLabel);
    cardLayout->addWidget(buyButton);


    int row = gridLayout->count() / 5;
    int col = gridLayout->count() % 5;
    gridLayout->addWidget(cardWidget, row, col, Qt::AlignHCenter);
}



void mainshop::loadCategoriesFromJson(const std::string& filePath) {

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        ErrorHandler::showWarning(this, "Помилка", "Не вдалося відкрити JSON файл!");
        return;
    }


    nlohmann::json jsonData;
    try {
        inputFile >> jsonData;
    } catch (const nlohmann::json::parse_error& e) {
        ErrorHandler::showCritical(this, "Помилка", "Помилка парсінга JSON: " + QString::fromStdString(e.what()));
        return;
    }


    categoryProducts.clear();

    auto loadCategory = [&](const std::string& categoryName, const std::string& jsonKey) {
        if (jsonData.contains(jsonKey) && jsonData[jsonKey].is_array()) {
            QList<Product> products;
            for (const auto& item : jsonData[jsonKey]) {
                try {

                    if (!item.contains("name") || !item["name"].is_string() ||
                        !item.contains("path") || !item["path"].is_string() ||
                        !item.contains("price") || !item["price"].is_number()) {
                        continue;
                    }

                    QString name = QString::fromStdString(item["name"]);
                    QString imagePath = QString::fromStdString(item["path"]);
                    double price = item["price"];


                    if (categoryName == "Продукти" && item.contains("expirationDate") && item["expirationDate"].is_string()) {
                        QString expirationDate = QString::fromStdString(item["expirationDate"]);
                        products.append(Food(name, imagePath, price, expirationDate));
                    } else if (categoryName == "Побутова техніка" && item.contains("warranty") && item["warranty"].is_string()) {
                        QString warranty = QString::fromStdString(item["warranty"]);
                        products.append(HomeAppliance(name, imagePath, price, warranty));
                    } else if (categoryName == "Зоотовари" && item.contains("animalType") && item["animalType"].is_string()) {
                        QString animalType = QString::fromStdString(item["animalType"]);
                        products.append(PetSupply(name, imagePath, price, animalType));
                    } else if (categoryName == "Одяг" && item.contains("material") && item["material"].is_string() &&
                               item.contains("size") && item["size"].is_string()) {
                        QString material = QString::fromStdString(item["material"]);
                        QString size = QString::fromStdString(item["size"]);
                        products.append(Clothing(name, imagePath, price, material, size));
                    } else if (categoryName == "Сантехніка" && item.contains("material") && item["material"].is_string()) {
                        QString material = QString::fromStdString(item["material"]);
                        products.append(Plumbing(name, imagePath, price, material));
                    } else if (categoryName == "Товари для дому" && item.contains("weight") && item["weight"].is_number() &&
                               item.contains("size") && item["size"].is_string()) {
                        double weight = item["weight"];
                        QString size = QString::fromStdString(item["size"]);
                        products.append(HomeGood(name, imagePath, price, weight, size));
                    } else if (categoryName == "Електроніка" && item.contains("operatingTime") && item["operatingTime"].is_string()) {
                        QString operatingTime = QString::fromStdString(item["operatingTime"]);
                        products.append(Electronic(name, imagePath, price, operatingTime));
                    } else {
                        ErrorHandler::logError("Пропущено продукт з категорії" + QString::fromStdString(categoryName) + "через відсутність специфічних даних.");
                    }
                } catch (const nlohmann::json::type_error& e) {
                    ErrorHandler::logError("Помилка в обробці продукта");
                }
            }

            categoryProducts[QString::fromStdString(categoryName)] = products;
            categories.append(QString::fromStdString(categoryName));
        } else {
            ErrorHandler::logError("Категорія" + QString::fromStdString(categoryName) + "не знайдена або містить некоректні данні.");
        }
    };


    loadCategory("Електроніка", "Електроніка");
    loadCategory("Одяг", "Одяг");
    loadCategory("Зоотовари", "Зоотовари");
    loadCategory("Сантехніка", "Сантехніка");
    loadCategory("Товари для дому", "Товари для дому");
    loadCategory("Продукти", "Продукти");
    loadCategory("Побутова техніка", "Побутова техніка");


    QList<Product> allProducts;
    QSet<QString> uniqueNames;

    for (auto it = categoryProducts.cbegin(); it != categoryProducts.cend(); ++it) {
        for (const Product& product : it.value()) {
            if (!uniqueNames.contains(product.name)) {
                uniqueNames.insert(product.name);
                allProducts.append(product);
            }
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allProducts.begin(), allProducts.end(), g);

    categoryProducts["Головна сторінка"] = allProducts;
    originalCategoryProducts = categoryProducts;
}



void mainshop::displayProductsForCategory(const QString& category) {

    QLayoutItem* child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }


    for (const auto& product : categoryProducts[category]) {
        addProductCard(product);
    }
}

void mainshop::onCategorySelected(QListWidgetItem* item) {
    QString category = item->text();
    displayProductsForCategory(category);
}

void mainshop::searchProducts(const QString& searchText) {

    QLayoutItem* child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }


    QSet<QString> uniqueNames;
    QList<Product> filteredProducts;

    for (const auto& category : std::as_const(categoryProducts)) {
        for (const Product& product : category) {
            if (product.name.contains(searchText, Qt::CaseInsensitive) &&
                !uniqueNames.contains(product.name)) {
                uniqueNames.insert(product.name);
                filteredProducts.append(product);
            }
        }
    }

    if (filteredProducts.isEmpty()) {
        QLabel* notFoundLabel = new QLabel("Товар не знайдено!");
        notFoundLabel->setAlignment(Qt::AlignCenter);
        notFoundLabel->setStyleSheet("font-size: 18px; color: red;");
        gridLayout->addWidget(notFoundLabel, 0, 0, Qt::AlignCenter);
    } else {
        for (const Product& product : filteredProducts) {
            addProductCard(product);
        }
    }
}

void mainshop::sortProductsAscending() {

    QString currentCategory = ui->categoryList->currentItem()->text();


    std::sort(categoryProducts[currentCategory].begin(), categoryProducts[currentCategory].end(),
              [](const Product& a, const Product& b) {
                  return a.price < b.price;
              });


    displayProductsForCategory(currentCategory);
}

void mainshop::sortProductsDescending() {

    QString currentCategory = ui->categoryList->currentItem()->text();


    std::sort(categoryProducts[currentCategory].begin(), categoryProducts[currentCategory].end(),
              [](const Product& a, const Product& b) {
                  return a.price > b.price;
              });

    displayProductsForCategory(currentCategory);
}

void mainshop::resetSorting() {
    QString currentCategory = ui->categoryList->currentItem()->text();

    if (originalCategoryProducts.contains(currentCategory)) {
        categoryProducts[currentCategory] = originalCategoryProducts[currentCategory];
        displayProductsForCategory(currentCategory);
    }
}


bool mainshop::isUserAdmin(const QString &login, const std::string &filePath) {
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        ErrorHandler::logError("Не вдалося відкрити файл" + QString::fromStdString(filePath));
        return false;
    }

    nlohmann::json jsonData;
    inputFile >> jsonData;

    for (const auto &user : jsonData) {
        if (user.contains("login") && QString::fromStdString(user["login"]) == login) {
            return user.value("isAdmin", false);
        }
    }

    ErrorHandler::logError("Користувача " + login + " не знайдено!");
    return false;
}

void mainshop::onAddItems() {
    if (categories.isEmpty()) {
        ErrorHandler::showWarning(this, "Помилка", "Список категорій пустий. Завантажте данні з JSON.");
        return;
    }

    addproductdialog *dialog = new addproductdialog(categories, this);
    dialog->setWindowTitle("Додати товар");
    connect(dialog, &addproductdialog::productAdded, this, &mainshop::onProductAdded);
    dialog->exec();
}

void mainshop::onProductAdded(const QString &name, double price, const QString &photoPath, const QString &category)
{
    Product newProduct;
    newProduct.name = name;
    newProduct.price = price;
    newProduct.imagePath = photoPath;

    categoryProducts[category].append(newProduct);

    refreshCategoryDisplay(category);
}

void mainshop::refreshCategoryDisplay(const QString &category)
{

    const QList<Product> &products = categoryProducts[category];


    QLayoutItem* child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }


    for (const Product &product : products) {
        addProductCard(product);
    }
}







