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
#include "libraryinfo.h"
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

    /**
     * @brief addLibraryToList Adds the library to the library list in the widget
     * @param library
     */
    void addLibraryToList(Library *library);

private slots:
    void on_libraryBrowser_customContextMenuRequested(const QPoint &pos);

    void on_fileBrowser_customContextMenuRequested(const QPoint &pos);

    void on_dependencyBrowser_customContextMenuRequested(const QPoint &pos);

    void on_packageLibraryViewer_customContextMenuRequested(const QPoint &pos);

    void on_actionInformazioni_triggered();

    void on_actionAggiungi_al_pacchetto_triggered();

    void on_actionNotALibrary_triggered();

private:
    Ui::PackageTab *ui;
    // Pacchetto che rappresenta il tab
    Package *package;
    // Lista delle librerie a cui può accedere
    QList<Library*> libraries;
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
    // Menu contestuale per la visualizzazione delle librerie aggiunte
    QMenu *addedLibrariesContextMenu = nullptr;

protected:
    /**
     * @brief addLibraryToPackage adds the library to the package
     * @param lib Library to add
     */
    void addLibraryToPackage(Library *lib);

    /**
     * @brief formatLibraryWidget Formats a widget to display the library informations
     * @param lib The library of the informations.
     */
    QTreeWidgetItem* formatLibraryWidget(Library *lib);
};

#endif // PACKAGETAB_H
