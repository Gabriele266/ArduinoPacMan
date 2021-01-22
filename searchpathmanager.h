#ifndef SEARCHPATHMANAGER_H
#define SEARCHPATHMANAGER_H

#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>

#include "packages/natural.h"
#include "newsearchpath.h"
#include "utils/utils.cpp"

namespace Ui {
class SearchPathManager;
}

class SearchPathManager : public QDialog
{
    Q_OBJECT

public:
    explicit SearchPathManager(QWidget *parent = nullptr);
    ~SearchPathManager();

    /// Aggiunge un elemento con quel nome
    void addEntry(QString path);

    /// Carica le informazioni base della finestra dalla lista baseEntries
    void loadFromList(QStringList* baseEntries);

    /// Restituisce una lista con tutti i percorsi di ricerca
    QStringList getEntriesList();

private slots:
    void on_addPath_clicked();

    void on_removePath_clicked();

    void onEntryAccept(QString entry);

signals:
    /// Chiamato quando si aggiunge un nuovo percorso di ricerca
    void pathAdded(QString newPath);

    /// Chiamato quando un percorso viene rimosso
    void pathRemoved(QString path);

private:
    Ui::SearchPathManager *ui;

    // Lista delle entries di ricerca
    QStringList entries;

    // Aggiorna il contatore delle librerie
    void updateItemsCounter();

    // Aggiorna la vista degli elementi
    void updateItemsView();
};

#endif // SEARCHPATHMANAGER_H
