#include "mainshop.h"
#include "ui_mainshop.h"
#include "mainwindow.h"
#include "shoppingcart.h"
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

    // Инициализация с логином
    ui->Button_user->setText(login);

    SetIconsFS();
    Catalog();
    loadCategories();


    cart = new shoppingcart(this);
    cart->setWindowTitle("Корзина");
    connect(this, &mainshop::productAddedToCart, cart, &shoppingcart::addProductToCart);
    connect(ui->search, &QLineEdit::textChanged, this, &mainshop::searchProducts);

    connect(ui->sort2, &QPushButton::clicked, this, &mainshop::sortProductsAscending); // Кнопка сортировки по возрастанию
    connect(ui->sort1, &QPushButton::clicked, this, &mainshop::sortProductsDescending); // Кнопка сортировки по убыванию
    connect(ui->resetButton, &QPushButton::clicked, this, &mainshop::resetSorting);





    QMenu *menu = new QMenu(this);

    QAction *logoutAction = new QAction("Вийти", this);          // Отображаем профиль
    menu->addAction(logoutAction);

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
    connect(ui->categoryList, &QListWidget::itemClicked, this, &mainshop::onCategorySelected);


    // Создаем layout для areaScroll
    QGridLayout* layout = new QGridLayout();
    layout->setSpacing(40);
    layout->setAlignment(Qt::AlignTop);

    QWidget* scrollContent = new QWidget();
    scrollContent->setLayout(layout);
    ui->scrollArea->setWidget(scrollContent);
    ui->scrollArea->setWidgetResizable(true);

    // Настроим стили для ScrollArea
    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "   background-color: white;" // Цвет фона ScrollArea
        "   border: none;" // Убираем границу
        "   padding: 10px;" // Отступы вокруг содержимого
        "   border-radius: 10px;" // Скругляем углы
        "}"
        );

    this->gridLayout = layout; // Сохраняем layout для дальнейшего использования

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
    cart->raise(); // Поднимаем окно на передний план
    cart->activateWindow();
}



void mainshop::addProductCard(const Product& product) {
    // Створюємо основний віджет для карточки товару
    QWidget* cardWidget = new QWidget();
    cardWidget->setFixedSize(200, 300); // Фіксований розмір карточки

    // Стилі для карточки товару
    cardWidget->setStyleSheet(
        "QWidget {"
        "    background-color: white;"
        "    border: 1px solid #dcdcdc;"
        "    border-radius: 10px;"
        "}"
        );

    // Створюємо макет для карточки
    QVBoxLayout* cardLayout = new QVBoxLayout(cardWidget);
    cardLayout->setAlignment(Qt::AlignCenter);

    // Додаємо зображення
    QLabel* imageLabel = new QLabel();
    imageLabel->setFixedSize(180, 180);
    imageLabel->setPixmap(QPixmap(product.imagePath).scaled(180, 180, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("border-radius: 10px; border-top: none; "); // Закруглені кути

    // Додаємо назву товару
    QLabel* nameLabel = new QLabel(product.name);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #333333; border: none;");

    // Додаємо ціну товару
    QLabel* priceLabel = new QLabel(QString::number(product.price, 'f', 2) + " грн");
    priceLabel->setAlignment(Qt::AlignCenter);
    priceLabel->setStyleSheet("color: #ff6600; font-size: 16px; font-weight: bold; border: none;");

    // Додаємо кнопки
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
        emit productAddedToCart(product); // Отправляем сигнал с информацией о товаре
        QMessageBox::information(this, "Додано до корзини", product.name + " успішно додано!");
    });



    // Додаємо всі віджети в макет карточки
    cardLayout->addWidget(imageLabel);
    cardLayout->addWidget(nameLabel);
    cardLayout->addWidget(priceLabel);
    cardLayout->addWidget(buyButton);

    // Додаємо карточку в сітку
    int row = gridLayout->count() / 5;
    int col = gridLayout->count() % 5;
    gridLayout->addWidget(cardWidget, row, col, Qt::AlignHCenter);
}



void mainshop::loadCategories() {
    // Очистимо категорії
    categoryProducts.clear();

    categoryProducts["Електроніка"] = {
        {"Телефон Iphone", ":/electronics/Iphone.png", 39999.99},
        {"Камера для зйомок", ":/electronics/Kamera.png", 14999.99},
        {"Ноутбук Lenovo", ":/electronics/Lenovo.png", 25000.00},
        {"Macbook Air", ":/electronics/Macbook.png", 49000.50},
        {"Фотоапарат", ":/electronics/Photoapparat.png", 18000.00},
        {"Телефон Samsung", ":/electronics/Samsung.png", 30000.99},
        {"Телефон Xiaomi", ":/electronics/Xiaomi.png", 14999.99}
    };

    categoryProducts["Одяг"] = {
        {"Куртка", ":/clothes/Jacket.png", 4000.99},
        {"Шапка", ":/clothes/Cap.png", 500.50},
        {"Джинси", ":/clothes/Jeans.png", 1799.99},
        {"Кофта", ":/clothes/Zipka.png", 1200.50},
        {"Кеди", ":/clothes/Keds.png", 2500.99},
        {"Кросівки", ":/clothes/Sneakers.png", 3999.99},
        {"Панама", ":/clothes/Panama.png", 699.50},
        {"Футболка", ":/clothes/T-shirt.png", 899.99},
        {"Шорти", ":/clothes/Shorts.png", 1499.50}
    };

    categoryProducts["Продукти"] = {
        {"Молоко", ":/products/Moloko.png", 37.50},
        {"Піцца Гала", ":/products/Pizza.png", 149.99},
        {"Сік Мультифрукт", ":/products/Sik.png", 46.99},
        {"Сметана 20%", ":/products/Smetana.png", 55.00},
        {"Снікерс", ":/products/Snickers.png", 28.99},
        {"Помідори", ":/products/Tomati.png", 69.50},
        {"Цукор 1кг", ":/products/Tsukor.png", 41.99}
    };

    categoryProducts["Побутова техніка"] = {
        {"Чайник Bosch", ":/equipment/Chainik.png", 1899.99},
        {"Холодильник Philips", ":/equipment/Holodilnik.png", 21999.50},
        {"Мікрохвильоква Samsung", ":/equipment/Mikrohvilyovka.png", 6999.99},
        {"Плита електрична Gorenje", ":/equipment/Pechka.png", 17999.50},
        {"Пилосос Philips", ":/equipment/Pilosos.png", 9999.99},
        {"Пральна машинка Bosch", ":/equipment/Stiralna_mahsinka.png", 15999.99},
        {"Праска Tefal", ":/equipment/Utug.png", 2599.50}
    };

    categoryProducts["Зоотовари"] = {
        {"Іграшка для тварин", ":/pet/Igrashka.png", 249.99},
        {"Корм для котів", ":/pet/Korm_dlya_kotiv.png", 399.99},
        {"Корм для папуг", ":/pet/Korm_dlya_popug.png", 249.50},
        {"Корм для собак", ":/pet/Korm_dlya_sobak.png", 549.99},
        {"Миска для корму", ":/pet/Miska.png", 249.50},
        {"Повідець", ":/pet/Povodok.png", 399.99}
    };

    categoryProducts["Сантехніка"] = {
        {"Фільтр", ":/plumbing/Filtr.png", 949.50},
        {"Розвідний ключ", ":/plumbing/Kluch_rozv.png", 1249.99},
        {"Кран сріблястий", ":/plumbing/Kran.png", 2499.99},
        {"Кран чорний", ":/plumbing/Kran2.png", 2899.50},
        {"Лічильник", ":/plumbing/Lichilnik.png", 1499.99},
        {"Труба", ":/plumbing/Truba.png", 699.50}
    };

    categoryProducts["Товари для дому"] = {
        {"Кружка", ":/item_for_home/Krujka.png", 349.99},
        {"Набір ложок та виделок", ":/item_for_home/Nabir_lojok_i_bydelok.png", 1249.50},
        {"Плед", ":/item_for_home/Pled.png", 749.99},
        {"Набір з 3 подушок", ":/item_for_home/Podushki.png", 1749.99},
        {"Сковорідка", ":/item_for_home/Skovoridka.png", 1299.50},
        {"Засіб для миття посуду", ":/item_for_home/Zasib_dlya_mittya_posudu.png", 299.99},
        {"Засіб для прання", ":/item_for_home/Zasib_dlya_prannya.png", 449.99}
    };



    QList<Product> allProducts;
    QSet<QString> uniqueNames; // Для хранения уникальных имен товаров

    for (auto it = categoryProducts.cbegin(); it != categoryProducts.cend(); ++it) {
        for (const Product& product : it.value()) {
            if (!uniqueNames.contains(product.name)) {
                uniqueNames.insert(product.name); // Добавляем имя товара в QSet
                allProducts.append(product);     // Добавляем товар в общий список
            }
        }
    }

    // Перемешиваем товары случайным образом
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allProducts.begin(), allProducts.end(), g);

    // Добавляем перемешанный список в "Головна сторінка"
    categoryProducts["Головна сторінка"] = allProducts;
    originalCategoryProducts = categoryProducts;

}


void mainshop::displayProductsForCategory(const QString& category) {
    // Удаляем все текущие виджеты из layout
    QLayoutItem* child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Добавляем карточки для выбранной категории
    for (const auto& product : categoryProducts[category]) {
        addProductCard(product);
    }
}

void mainshop::onCategorySelected(QListWidgetItem* item) {
    QString category = item->text();
    displayProductsForCategory(category);
}

void mainshop::searchProducts(const QString& searchText) {
    // Удаляем все текущие виджеты из layout
    QLayoutItem* child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Найдем товары, соответствующие тексту поиска
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
    // Получаем текущую категорию
    QString currentCategory = ui->categoryList->currentItem()->text();

    // Сортируем товары в категории
    std::sort(categoryProducts[currentCategory].begin(), categoryProducts[currentCategory].end(),
              [](const Product& a, const Product& b) {
                  return a.price < b.price; // Сортировка по возрастанию
              });

    // Обновляем отображение товаров
    displayProductsForCategory(currentCategory);
}

void mainshop::sortProductsDescending() {
    // Получаем текущую категорию
    QString currentCategory = ui->categoryList->currentItem()->text();

    // Сортируем товары в категории
    std::sort(categoryProducts[currentCategory].begin(), categoryProducts[currentCategory].end(),
              [](const Product& a, const Product& b) {
                  return a.price > b.price; // Сортировка по убыванию
              });

    // Обновляем отображение товаров
    displayProductsForCategory(currentCategory);
}

void mainshop::resetSorting() {
    QString currentCategory = ui->categoryList->currentItem()->text(); // Текущая категория

    if (originalCategoryProducts.contains(currentCategory)) {
        categoryProducts[currentCategory] = originalCategoryProducts[currentCategory]; // Восстановление
        displayProductsForCategory(currentCategory); // Обновляем отображение товаров
    }
}





