#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QDialog>
#include <QList>
#include "Product.h"     // Подключаем структуру Product

namespace Ui {
class shoppingcart;
}

class shoppingcart : public QDialog
{
    Q_OBJECT

public:
    explicit shoppingcart(QWidget *parent = nullptr);
    explicit shoppingcart(const QList<Product>& products, QWidget *parent = nullptr);
    ~shoppingcart();

private:
    Ui::shoppingcart *ui;
    QList<Product> cartProducts;
    double totalCost = 0.0;
    int totalCount = 0;

    double extractPriceFromItem(const QString& itemText);
    void updateSummary();


public slots:
    void addProductToCart(const Product& product);

private slots:
    void on_pushButton_2_clicked(); // Подтверждение покупки
    void on_pushButton_clicked();   // Удаление товара из корзины
};

#endif // SHOPPINGCART_H
