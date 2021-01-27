#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextStream>
#include <QLabel>


// Dialoghi addizionali
#include "gui/packagemanager.h"
#include "gui/generalstatusbar.h"

// Costrutti logici
#include "packages/package.h"
#include "packages/library.h"

// Altri dialoghi
#include "newpackagedialog.h"
#include "searchpathmanager.h"

// Threads per la gestione delle operazioni di IO
#include "threads/searchpathlistwriter.h"
#include "threads/searchpathlistreader.h"
#include "threads/packagereader.h"

#include "file_types/libsearchpathlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
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

private:
    Ui::MainWindow *ui;

    // Gestore dei paccchetti
    PackageManager *packageManager = new PackageManager();

    // Creo una status bar
    GeneralStatusBar *statusBar = new GeneralStatusBar();

    // Lista dei percorsi di ricerca delle librerie
    LibSearchPathList librariesSearchPath;

    // Percorso in cui salvare i percorsi di ricerca
    QString libSearchPath = getHomePath() + "libsources.src";
};
#endif // MAINWINDOW_H
