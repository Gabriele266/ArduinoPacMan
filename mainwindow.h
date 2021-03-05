#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextStream>
#include <QLabel>

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

    /// Carica i percorsi di ricerca dal file corretto
    void loadSearchPathFromFile();

    /**
     * @brief loadLibraryList starts the search of the libraries in the search paths.
     */
    void loadLibraryList();

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
    // Gestisce la creazione di un nuovo pacchetto
    void newPackage();

    /// Mostra la scheda home
    void showHomePage();

    /// Apre un nuovo pacchetto
    void openPackage();

    /// Restituisce l'indice del pacchetto corrente
    int getPackageIndex(Natural tabIndex);

    /// Restituisce il pacchetto con quell' indice di tab
    Package* getPackageFromTabIndex(Natural tabIndex);

    /// Aggiorna le informazioni del titolo in base al tab corrente
    void updateTitleInfo();

    // Aggiorna la barra di stato
    void updateStatusBar();

    /// Restituisce il pacchetto corrente
    Package* getCurrentPackage();

    /// Determina se il tab corrente è di un pacchetto
    bool currentTabIsPackage();

    /// Aggiunge un pacchetto alla vista
    Tab* addPackageToView(Package *package);

    /// Rimuove un tab
    void removeTab(Natural tabIndex);

    /**
     * @brief isOpenedPackage determina se il pacchetto passato è già aperto nell' ambiente
     * @param package Pacchetto da controllare
     * @return true se è già aperto
     */
    bool isOpenedPackage(Package *package);
};

#endif // MAINWINDOW_H
