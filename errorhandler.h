#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QWidget>

class ErrorHandler {
public:
    static void showWarning(QWidget *parent, const QString &title, const QString &message);
    static void showCritical(QWidget *parent, const QString &title, const QString &message);
    static void showInfo(QWidget *parent, const QString &title, const QString &message);
    static void logError(const QString &message);
};

#endif // ERRORHANDLER_H
