/*
 * Autore: cavallo gabriele
 * Rappresenta un tab in un gestore di pacchetti per gestirne la visualizzazione
 * */
#ifndef PACKAGETAB_H
#define PACKAGETAB_H

#include <QWidget>
#include <QString>
#include <QTreeWidget>

#include "../packages/package.h"
#include "tab.h"

namespace Ui {
class PackageTab;
}

class PackageTab : public QWidget, public Tab
{
    Q_OBJECT

public:
    explicit PackageTab(Package *package, QWidget *parent = nullptr );
    ~PackageTab();

    /// Imposta i tag del tab
    void setTags(QString tags);

    /// Restituisce i tag relativi al tab
    QString getTags();

    /// Determina se il tab è visibile o no
    bool isVisible() {return opened;}

    /// Restituisce l'indirizzo del pacchetto a cui si riferisce
    Package* getPackage();

    // Restituisce l'indirizzo del browser dei file
    QTreeWidget* getFileBrowser();

    /// Restituisce un puntatore al browser delle dipendenze
    QTreeWidget* getDependencyBrowser();

private:
    Ui::PackageTab *ui;
    // Pacchetto che rappresenta il tab
    Package *package;
    // Tag associato al tab
    QString tag;
    // Indica se il tab è visualizzato o no
    bool opened = true;
};

#endif // PACKAGETAB_H
