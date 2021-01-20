/*
 * Rappresenta un gestore di pacchetti come tabbed-widget
 * */

#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include "../packages/package.h"
#include "packagetab.h"
#include "threads/sourcesloader.h"

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

private slots:
    void on_surfaceManager_currentChanged(int index);

signals:
    // Emesso quando il tab è stato cambiato
    void tabChanged(unsigned int newTab);
private:

    // Funzione chiamata ogni volta che si cambia pacchetto

    // Lista di pacchetti
    QList<Package *>packages;

    Ui::PackageManager *ui;
};

#endif // PACKAGEMANAGER_H
