#ifndef MAINSHOP_H
#define MAINSHOP_H

#include <QMainWindow>
#include <QListWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMenu>
#include <QMap>
#include "product.h"
#include "shoppingcart.h"

namespace Ui {
class mainshop;
}

class mainshop : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainshop(QWidget *parent = nullptr);
    explicit mainshop(const QString &login, QWidget *parent = nullptr);
    ~mainshop();

private:
    Ui::mainshop *ui;

    void SetIconsFS();
    void Catalog();
    QGridLayout* gridLayout; // Для хранения текущего layout
    QMap<QString, QList<Product>> categoryProducts;
    QMap<QString, QList<Product>> originalCategoryProducts;
    void loadCategories();
    void addProductCard(const Product& product);
    void displayProductsForCategory(const QString& category);
    shoppingcart* cart; // Указатель на корзину
    void searchProducts(const QString& searchText);





private slots:
    void logout();
    void on_cart_clicked();
    void onCategorySelected(QListWidgetItem* item);
    void sortProductsAscending();
    void sortProductsDescending();
    void resetSorting();

signals:
    void productAddedToCart(const Product& product);

};

#endif // MAINSHOP_H
