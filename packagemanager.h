/*
 * Autore: cavallo gabriele
 * Rappresenta un gestore di paccketto
 * */
#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QString>
#include <QStringList>
#include <QTabWidget>
#include <QList>
#include <QtDebug>

#include "package.h"
#include "packagetab.h"


/// Rappresenta un gestore di pacchetti in una interfaccia
class PackageManager
{
public:
    PackageManager();

    /// Gestisce l'apertura e la visualizzazione del pacchetto e dei relativi elementi della interfaccia per il pacchetto presente in quel percorso
    bool openPackage(QString path);

    /// Aggiunge un pacchetto e lo mostra
    void addPackage(Package *pack, bool is_new = false, bool show = true);

    /// Mostra il paccketto con quell' indice
    void showPackage(unsigned int index);

    /// Imposta il gestore dei tab
    void setUiElement(QTabWidget *manager);
private:
    // Gestore dei tab
    QTabWidget *widget_manager;

    // Numero di schede aperte
    unsigned int opened_tabs = 0;

    // Lista dei pacchetti
    QList<Package* > packages;
};

#endif // PACKAGEMANAGER_H
