#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class addproductdialog;
}

class addproductdialog : public QDialog
{
    Q_OBJECT

public:
    explicit addproductdialog(const QStringList &categories, QWidget *parent = nullptr);
    ~addproductdialog();

private slots:
    void onSelectPhoto(); // Слот выбора фото
    void onAddProduct();  // Слот добавления товара


signals:
    void productAdded(const QString &name, double price, const QString &photoPath, const QString &category);

private:
    Ui::addproductdialog *ui;
    QString selectedPhotoPath;
    QStringList categories;
};

#endif // ADDPRODUCTDIALOG_H
