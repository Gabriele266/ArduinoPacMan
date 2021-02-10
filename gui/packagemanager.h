/*
 * Rappresenta un gestore di pacchetti come tabbed-widget
 * */

#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include "../packages/package.h"
#include "packagetab.h"
#include "threads/sourcesloader.h"
#include "threads/srcdependencylister.h"
#include "gui/homepage.h"

#include <QWidget>
#include <QTabWidget>
#include <QList>
#include <QStringList>

#include "utils/macros.h"

class PackageManager
{
public:
    PackageManager();

    GETTER_SETTERC(QTabWidget*, tabWidget, TabWidget,
                   Imposta il widget che si occuperà della visualizzazione dei tab,
                   Restituisce il widget che si occupa della visualizzazione)

    /// Aggiunge un pacchetto alla lista e lo visualizza nel controllo
    PackageTab* addPackage(Package *pack);

    /// Inizializza il gestore
    void init();

    /// Restituisce il pacchetto corrente
    Package* getCurrentPackage();

    /// Determina se il tab selezionato è un pacchetto o qualcos altro
    bool isCurrentPackage();

    /// Restituisce l'indice del pacchetto corrente, se attualmente è selezionato
    /// se ci si trova in una scheda che non è un pacchetto restituisce -1
    unsigned int getCurrentPackageIndex();

    /// Determina se sono presenti dei pacchetti in uso (aggiunti) indifferentemente se sono visibili o no
    bool hasPackages();

    /// Restituisce il numero di pacchetti che sono stati aggiunti all' ambiente
    unsigned int getPackagesCount();

    /// Avvia la ricerca delle dipendenze per il pacchetto package
    void startDependencyIndexer(Package *package, QTreeWidget* widget);
private:
    // Lista di pacchetti
    QList<Package *>packages;

    // Thread per il caricamento delle dipendenze di un pacchetto
    SrcDependencyLister *lister = new SrcDependencyLister();

    // Widget che gestisce la visualizzazione
    QTabWidget *tabWidget = nullptr;
};

#endif // PACKAGEMANAGER_H
