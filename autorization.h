#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QMainWindow>

namespace Ui {
class autorization;
}

class autorization : public QMainWindow
{
    Q_OBJECT

public:
    explicit autorization(QWidget *parent = nullptr);
    ~autorization();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_checkBoxpassword_stateChanged(int arg1);

private:
    Ui::autorization *ui;

    void SetIconsFA();
};

#endif // AUTORIZATION_H
