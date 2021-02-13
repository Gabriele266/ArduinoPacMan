#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class HomePage;
class PackageManager;

#include <QMainWindow>
#include <QDebug>
#include <QTextStream>
#include <QLabel>


// Dialoghi addizionali
#include "gui/generalstatusbar.h"
#include "gui/packagemanager.h"
#include "gui/tab.h"

// Costrutti logici
#include "packages/package.h"
#include "packages/library.h"

// Altri dialoghi
#include "newpackagedialog.h"
#include "searchpathmanager.h"

#include "utils/settings_manager.cpp"

// Threads per la gestione delle operazioni di IO
#include "threads/searchpathlistwriter.h"
#include "threads/searchpathlistreader.h"
#include "threads/packagereader.h"

#include "file_types/libsearchpathlist.h"

#include "packageinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, PackageManager
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /// Aggiorna le informazioni del titolo in base al tab corrente
    void updateTitleInfo();

    // Aggiorna la barra di stato
    void updateStatusBar();

private slots:
    void on_actionNuova_finestra_triggered();

    void on_pushButton_clicked();

    void on_actionNuovo_pacchetto_triggered();

    void on_packageManager_currentChanged(int index);

    void onPackageManagerTabChange(unsigned int newTab);
    void on_actionPercorsi_ricerca_librerie_triggered();

    /// Chiamato quando si aggiunge un percorso di ricerca
    void aggiungiPercorsoRicercaTriggered(QString path);

    /// Chiamato quando si rimuove un percorso di ricerca
    void rimuoviPercorsoRicerca(QString path);

    /// Chiamato quando si modifica un percorso di ricerca dal relativo dialogo
    void modificaPercorsoRicerca(Natural index, QString old_val, QString new_val);
    void on_actionApri_pacchetto_triggered();

    /// Chiamato quando un tab necessita di creare un nuovo pacchetto
    void onNewPackageRequired();

    /// Chiamato quando si apre un nuovo pacchetto
    void onOpenPackageRequired();
    void on_actionScheda_home_triggered();

    void on_actionSchede_a_sinistra_triggered();

    void on_widgetManager_currentChanged(int index);

    void on_actionPropriet_pacchetto_triggered();

private:
    Ui::MainWindow *ui;

    // Creo una status bar
    GeneralStatusBar *statusBar = new GeneralStatusBar();

    // Lista dei percorsi di ricerca delle librerie
    LibSearchPathList librariesSearchPath;

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

    /// Restituisce il pacchetto corrente
    Package* getCurrentPackage();
};

#endif // MAINWINDOW_H
