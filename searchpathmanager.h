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

    /// Carica le informazioni base della finestra dalla lista baseEntries
    void loadFromList(QStringList* baseEntries);

    /// Restituisce una lista con tutti i percorsi di ricerca
    QStringList getEntriesList();

private slots:
    void on_addPath_clicked();

    void on_removePath_clicked();

    void on_editCurrent_clicked();

signals:
    /// Chiamato quando si aggiunge un nuovo percorso di ricerca
    void pathAdded(QString newPath);

    /// Chiamato quando un percorso viene rimosso
    void pathRemoved(QString path);

    /// Chiamato quando si modifica un percorso
    /// \arg oldVal indica il percorso vecchio
    /// \arg newVal indica il percorso nuovo
    void pathEdited(Natural index, QString oldVal, QString newVal);

private:
    Ui::SearchPathManager *ui;

    // Lista delle entries di ricerca
    QStringList entries;

protected:

    // Aggiorna il contatore delle librerie
    void updateItemsCounter();

    // Aggiorna la vista degli elementi
    void updateItemsView();

    /// Aggiunge un elemento con quel nome
    void addEntry(QString path);

    /// Modifica l'elemento con quell' indice applicando il nuovo nome
    void editItem(Natural index, QString newVal);
};

#endif // SEARCHPATHMANAGER_H
