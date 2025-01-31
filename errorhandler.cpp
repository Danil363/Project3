#include "ErrorHandler.h"

void ErrorHandler::showWarning(QWidget *parent, const QString &title, const QString &message) {
    QMessageBox::warning(parent, title, message);
}

void ErrorHandler::showCritical(QWidget *parent, const QString &title, const QString &message) {
    QMessageBox::critical(parent, title, message);
}

void ErrorHandler::showInfo(QWidget *parent, const QString &title, const QString &message) {
    QMessageBox::information(parent, title, message);
}

void ErrorHandler::logError(const QString &message) {
    qDebug() << "Помилка:" << message;
}
