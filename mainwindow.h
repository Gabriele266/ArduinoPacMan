#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextStream>
#include <QLabel>

#include "library.h"
#include "newpackagedialog.h"
#include "gui/packagemanager.h"
#include "package.h"

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

private slots:
    void on_actionNuova_finestra_triggered();

    void on_pushButton_clicked();

    void on_actionNuovo_pacchetto_triggered();

    void on_packageManager_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    QString endl = "\n";

    // Gestore dei paccchetti
    PackageManager *packageManager = new PackageManager();
};
#endif // MAINWINDOW_H
