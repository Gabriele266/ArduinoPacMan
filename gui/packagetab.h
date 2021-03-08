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
#include <QMessageBox>

#include "../packages/package.h"
#include "librarytab.h"
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

signals:
    /**
     * @brief tabAddRequired emitted when this widget needs to show another widget to the view
     * @param tab the tab to show.
     */
    void libraryTabAdd(LibraryTab *tab);

    /**
     * @brief fileViewerTabAdd emitted when this widget requires the showing of a new tab
     * @param fileToView the file we wish to display
     */
    void fileTabAdd(QString fileToView);

    /**
     * @brief dependencyTabAdd emitted when this widget requires the showing of a dependency in new tab
     * @param dependency
     */
    void dependencyTabAdd(Dependency *dependency);

private slots:
    void on_libraryBrowser_customContextMenuRequested(const QPoint &pos);

    void on_fileBrowser_customContextMenuRequested(const QPoint &pos);

    void on_dependencyBrowser_customContextMenuRequested(const QPoint &pos);

    void on_packageLibraryViewer_customContextMenuRequested(const QPoint &pos);

    void on_actionInformazioni_triggered();

    void on_actionAggiungi_al_pacchetto_triggered();

    void on_actionNotALibrary_triggered();

    void on_actionInformazioniLibreria_triggered();

    void on_actionInformazioni_libreria_triggered();

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

    /**
     * @brief getSelectedLibraryFromList Returns the selected library from the libraries list
     * @return the library object
     */
    Library* getSelectedLibraryFromList();
};

#endif // PACKAGETAB_H
