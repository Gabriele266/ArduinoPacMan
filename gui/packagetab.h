/*
 * Autore: cavallo gabriele
 * Rappresenta un tab in un gestore di pacchetti per gestirne la visualizzazione
 * */
#ifndef PACKAGETAB_H
#define PACKAGETAB_H

#include <QWidget>
#include <QString>
#include <QTreeWidget>
#include <QMenu>

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

    /// Restituisce l'indirizzo del gestore delle librerie trovate
    QTreeWidget* getFoundLibrariesManager();

private slots:
    void on_libraryBrowser_customContextMenuRequested(const QPoint &pos);

    void on_fileBrowser_customContextMenuRequested(const QPoint &pos);

    void on_dependencyBrowser_customContextMenuRequested(const QPoint &pos);

private:
    Ui::PackageTab *ui;
    // Pacchetto che rappresenta il tab
    Package *package;
    // Tag associato al tab
    QString tag;
    // Indica se il tab è visualizzato o no
    bool opened = true;
    // Menu contestuale per le librerie
    QMenu *librariesContextMenu = nullptr;
    // Menu contestuale per la visualizzazione file
    QMenu *filesContextMenu = nullptr;
    // Menu contestuale per la visualizzazione dipendenze
    QMenu *dependencyContextMenu = nullptr;
};

#endif // PACKAGETAB_H
