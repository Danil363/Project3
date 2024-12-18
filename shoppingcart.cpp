#include "shoppingcart.h"
#include "ui_shoppingcart.h"
#include <QMessageBox>

shoppingcart::shoppingcart(QWidget *parent)
    : QDialog(parent), ui(new Ui::shoppingcart)
{
    ui->setupUi(this);
    this->setFixedSize(600, 500);


}

shoppingcart::shoppingcart(const QList<Product>& products, QWidget *parent)
    : QDialog(parent), ui(new Ui::shoppingcart)
{
    ui->setupUi(this);
    this->setFixedSize(600, 500);



    // Добавляем все переданные товары в корзину
    for (const Product& product : products) {
        addProductToCart(product);
    }
}



shoppingcart::~shoppingcart()
{
    delete ui;
}

void shoppingcart::addProductToCart(const Product& product) {
    // Создаём элемент для QListWidget
    QListWidgetItem* item = new QListWidgetItem(product.name + " | Кількість: 1 | Ціна: " + QString::number(product.price, 'f', 2) + " грн");

    // Устанавливаем выравнивание текста
    item->setTextAlignment(Qt::AlignHCenter);
    ui->ItemsInCart->setSpacing(2);

    // Добавляем элемент в список
    ui->ItemsInCart->addItem(item);

    // Обновляем сумму и количество
    totalCost += product.price;
    totalCount += 1;

    updateSummary();
}


void shoppingcart::updateSummary() {
    ui->cost->setText(QString::number(totalCost, 'f', 2) + " грн");
    ui->count->setText(QString::number(totalCount));
}


void shoppingcart::on_pushButton_2_clicked()
{
    if (ui->ItemsInCart->count() == 0) { // Проверяем, есть ли элементы в QListWidget
        QMessageBox::warning(this, "Помилка", "Корзина порожня! Додайте товари перед покупкою.");
        return;
    }


    QString details;
    double total = 0.0;

    for (int i = 0; i < ui->ItemsInCart->count(); ++i) {
        QString itemText = ui->ItemsInCart->item(i)->text();
        details += itemText + "\n";

        // Извлекаем цену из строки для подсчета общей суммы
        QStringList parts = itemText.split("Ціна: ");
        if (parts.size() > 1) {
            QString priceStr = parts[1].split(" грн").first();
            total += priceStr.toDouble();
        }
    }

    details += "\nЗагальна сума: " + QString::number(total, 'f', 2) + " грн";
    QMessageBox::information(this, "Дякуємо за покупку!", "Ваше замовлення:\n" + details);

    // Очистить корзину
    ui->ItemsInCart->clear();
    totalCost = 0.0;
    totalCount = 0;
    updateSummary();

}



void shoppingcart::on_pushButton_clicked()
{
    // Получаем текущий выбранный элемент
    QListWidgetItem* currentItem = ui->ItemsInCart->currentItem();

    if (currentItem) {
        // Извлекаем цену из текста элемента до его удаления
        double price = extractPriceFromItem(currentItem->text());

        // Удаляем текущий элемент из списка
        delete ui->ItemsInCart->takeItem(ui->ItemsInCart->row(currentItem));

        // Обновляем счетчики
        totalCount--;
        totalCost -= price;

        updateSummary();
    }
}


double shoppingcart::extractPriceFromItem(const QString& itemText) {
    QStringList parts = itemText.split('|');
    if (parts.size() >= 2) {
        QString priceText = parts[2].trimmed(); // "Ціна: XX грн"
        priceText = priceText.remove("Ціна: ").remove(" грн");
        return priceText.toDouble();
    }
    return 0.0;
}

