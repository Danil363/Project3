#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QDialog>
#include <QList>
#include "Product.h"

namespace Ui {
class shoppingcart;
}

class shoppingcart : public QDialog
{
    Q_OBJECT

public:
    explicit shoppingcart(QWidget *parent = nullptr);
    explicit shoppingcart(const QList<Product>& products,const QString& login, QWidget *parent = nullptr);
    ~shoppingcart();

private:
    Ui::shoppingcart *ui;
    QList<Product> cartProducts;
    double totalCost = 0.0;
    int totalCount = 0;
    double userBalance;
    QString currentUserLogin;

    double extractPriceFromItem(const QString& itemText);
    void updateSummary();
    void loadUserBalance();
    void updateUserBalanceInJson();
    void logPurchaseToCsv(const QString& details, double total, double balanceAfterPurchase);


public slots:
    void addProductToCart(const Product& product);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // SHOPPINGCART_H
