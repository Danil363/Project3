#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "registration.h"
#include "autorization.h"
#include <qboxlayout>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    this->setFixedSize(800,600);

    this->setWindowTitle("Oriventa Shop");
    QIcon icon(":/images/OS.PNG");
    this->setWindowIcon(icon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    autorization* window = new autorization;
    this->close();
    window->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    registration* window = new registration;
    this->close();
    window->show();
}



