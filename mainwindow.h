#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextStream>
#include <QLabel>

#include "packages/library.h"
#include "newpackagedialog.h"
#include "gui/packagemanager.h"
#include "gui/generalstatusbar.h"
#include "packages/package.h"
#include "searchpathmanager.h"
#include "threads/searchpathlistwriter.h"
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

    void aggiungiPercorsoRicercaTriggered(QString path);
private:
    Ui::MainWindow *ui;

    // Gestore dei paccchetti
    PackageManager *packageManager = new PackageManager();

    // Creo una status bar
    GeneralStatusBar *statusBar = new GeneralStatusBar();

    // Lista dei percorsi di ricerca delle librerie
    LibSearchPathList librariesSearchPath;
};
#endif // MAINWINDOW_H
