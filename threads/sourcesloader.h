/* Autore: cavallo gabriele
 * Rappresenta un thread di caricamento dei file sorgente in un percorso
 * */
#ifndef SOURCESLOADER_H
#define SOURCESLOADER_H

#include <QThread>
#include <QString>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QTreeWidget>
#include <QMessageBox>

#include "utils/utils.cpp"
#include "packages/source.h"
#include "packages/package.h"
#include "utils/macros.h"
#include "gui/packagemanager.h"

/// Rappresenta un thread di caricamento sorgenti
class SourcesLoader : public QThread
{
public:
    SourcesLoader();

    /// Esegue il thread
    void run();

    /// Imposta l'albero a cui aggiungere i file e le cartelle sorgenti trovate
    void setDestination(QTreeWidget *item);

    /// Imposta il percorso di ricerca dei file
    void setSearchPath(QString path);

    /// Imposta il pacchetto su cui lavorare
    SETTER(Package*, package, Package)

private:
    // Percorso di ricerca del thread
    QString search_path;

    // Lista di stringhe in cui mettere i nomi dei file sorgenti trovati
    QTreeWidget *destination = nullptr;

    // Pacchetto
    Package *package = nullptr;

protected:
    /// Appende le entryes della cartella all' item
    void appendEntries(QTreeWidgetItem *item, QDir dir);
};

#endif // SOURCESLOADER_H
