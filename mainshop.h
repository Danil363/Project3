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

    bool isUserAdmin(const QString &login, const std::string &filePath);

private:
    Ui::mainshop *ui;

    QStringList categories;

    void SetIconsFS();
    void Catalog();
    QGridLayout* gridLayout;
    QMap<QString, QList<Product>> categoryProducts;
    QMap<QString, QList<Product>> originalCategoryProducts;
    void loadCategories();
    void loadCategoriesFromJson(const std::string& filePath);
    void addProductCard(const Product& product);
    void displayProductsForCategory(const QString& category);
    shoppingcart* cart; // Указатель на корзину
    void searchProducts(const QString& searchText);
    void refreshCategoryDisplay(const QString &category);





private slots:
    void logout();
    void onAddItems();
    void on_cart_clicked();
    void onCategorySelected(QListWidgetItem* item);
    void sortProductsAscending();
    void sortProductsDescending();
    void resetSorting();
    void onProductAdded(const QString &name, double price, const QString &photoPath, const QString &category);

signals:
    void productAddedToCart(const Product& product);

};

#endif // MAINSHOP_H
