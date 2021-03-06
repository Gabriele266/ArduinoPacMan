#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextStream>
#include <QLabel>
#include <QtConcurrent/QtConcurrent>
#include <QProcess>

// Dialoghi addizionali
#include "gui/generalstatusbar.h"
#include "gui/tab.h"
#include "gui/homepage.h"
#include "gui/packagetab.h"

// Costrutti logici
#include "packages/package.h"
#include "packages/library.h"
#include "packages/sourceinfo.h"

// Altri dialoghi
#include "gui/newpackagedialog.h"
#include "gui/searchpathmanager.h"
#include "gui/packageinfo.h"

#include "utils/settings_manager.cpp"

// Threads per la gestione delle operazioni di IO
#include "threads/searchpathlistwriter.h"
#include "threads/searchpathlistreader.h"
#include "threads/packagereader.h"
#include "threads/sourcesloader.h"
#include "threads/srcdependencylister.h"
#include "threads/librariesloader.h"

#include "settings/libsearchpathlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNuova_finestra_triggered();
    void on_pushButton_clicked();
    void on_actionNuovo_pacchetto_triggered();
    void on_packageManager_currentChanged(int index);
    void on_actionPercorsi_ricerca_librerie_triggered();
    void aggiungiPercorsoRicercaTriggered(QString path);
    void rimuoviPercorsoRicerca(QString path);
    void modificaPercorsoRicerca(Natural index, QString old_val, QString new_val);
    void on_actionApri_pacchetto_triggered();
    void onNewPackageRequired();
    void onOpenPackageRequired();
    void on_actionScheda_home_triggered();
    void on_actionSchede_a_sinistra_triggered();
    void on_widgetManager_currentChanged(int index);
    void on_actionPropriet_pacchetto_triggered();
    void on_widgetManager_tabCloseRequested(int index);
    void on_actionChiudi_tutte_le_schede_aperte_triggered();
    void on_actionApri_nel_terminale_triggered();
    void on_actionApri_nel_gestore_dei_file_triggered();
    void on_actionEsci_triggered();

    /**
     * @brief loadSearchPathFromFile loads the search path list from the file
     */
    void loadSearchPathFromFile();

    /**
     * @brief loadLibraryList starts the search of the libraries in the search paths.
     */
    void loadLibraryList();

    void on_actionSposta_scheda_alla_fine_triggered();

private:
    Ui::MainWindow *ui;

    // Creo una status bar
    GeneralStatusBar *statusBar = new GeneralStatusBar();

    // Lista dei percorsi di ricerca delle librerie
    LibSearchPathList librariesSearchPath;

    // Lista con le librerie trovate nei percorsi di ricerca
    QList<Library*> foundLibraries;

    // Indica lo stato di validazione della lista delle librerie
    bool foundLibValidationState = true;

    // Impostazioni della applicazione
    Settings settings;

    // Lista con i pacchetti
    QList<Package*> packageList;

    // Lista di tutti i tab
    QList<Tab*> tabs;

protected:
    /**
     * @brief newPackage Manages the creation of a new package
     */
    void newPackage();

    /**
     * @brief showHomePage Shows the home page tab on the tabManager
     */
    void showHomePage();

    /**
     * @brief openPackage Handles the opening of the package
     */
    void openPackage();

    /**
     * @brief getPackageIndex Returns the index of the package that the tab index referres to
     * @param tabIndex The index of the tab
     * @return the index(if exists) of the package in the list packageList.
     */
    int getPackageIndex(Natural tabIndex);

    /**
     * @brief getPackageFromTabIndex Returns the package that the tab referred by his index represents
     * @param tabIndex the tab index in the manager
     * @return the package if the tab manages a package, nullptr otherwise
     */
    Package* getPackageFromTabIndex(Natural tabIndex);

    /**
     * @brief updateTitleInfo updates the title informations based on the current tab
     */
    void updateTitleInfo();

    /**
     * @brief updateStatusBar updates the status bar based on the current tab
     */
    void updateStatusBar();

    /**
     * @brief getCurrentPackage returns the current package opened in the tab manager
     * @return the address of the package or, if the current tab does not refer to a package, nullptr
     */
    Package* getCurrentPackage();

    /**
     * @brief currentTabIsPackage checks if the current tab is a package manager or not
     * @return true if it is
     */
    bool currentTabIsPackage();

    /**
     * @brief addPackageToView adds the package to the widget manager, initializes his tab and displays it
     * @param package the package to add
     * @return The tab created to display it (nullptr in case of errors)
     */
    Tab* addPackageToView(Package *package);

    /**
     * @brief removeTab removes the tab with the given index
     * @param tabIndex the tab index
     */
    void removeTab(Natural tabIndex);

    /**
     * @brief isOpenedPackage determina se il pacchetto passato è già aperto nell' ambiente
     * @param package Pacchetto da controllare
     * @return true se è già aperto
     */
    bool isOpenedPackage(Package *package);
};

#endif // MAINWINDOW_H
