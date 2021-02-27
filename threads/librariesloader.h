/* Autore: cavallo gabriele
 * Rappresenta un thread per il caricamento delle librerie da un percorso di partenza
 * */

#ifndef LIBRARIESLOADER_H
#define LIBRARIESLOADER_H

#include <QThread>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QList>

#include "../utils/utils.h"
#include "../packages/library.h"

/// Rappresenta un caricatore di librerie su thread separato
class LibrariesLoader : public QThread
{
public:
    LibrariesLoader();

    /// Esegue il thread
    void run();

    /// Imposta il percorso in cui cercare le librerie
    void setSearchPath(QString path);

    /// Imposta l'albero su cui aggiungere le librerie
    void setDestination(QTreeWidget *dest);

    /// Imposta la lista a cui devono essere aggiunte le librerie trovate
    void setLibrariesDestination(QList<Library*> *libraries);
private:
    // Percorso in cui cercare
    QString path;
    // Albero a cui aggiungere i risultati
    QTreeWidget *destination;
    // Lista di librerie
    QList<Library*> *libraries;
};

#endif // LIBRARIESLOADER_H
