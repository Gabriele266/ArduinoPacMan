/*
 * Rappresenta un gestore di pacchetti come tabbed-widget
 * */

#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include "../package.h"
#include "packagetab.h"

#include <QWidget>
#include <QTabWidget>
#include <QList>
#include <QStringList>

namespace Ui {
class PackageManager;
}

class PackageManager : public QWidget
{
    Q_OBJECT

public:
    explicit PackageManager(QWidget *parent = nullptr);
    ~PackageManager();

    /// Aggiunge un pacchetto alla lista e lo visualizza nel controllo
    void addPackage(Package *pack);


private slots:
    void on_surfaceManager_currentChanged(int index);

private:
    Ui::PackageManager *ui;

    // Lista di pacchetti
    QList<Package *>packages;
};

#endif // PACKAGEMANAGER_H
