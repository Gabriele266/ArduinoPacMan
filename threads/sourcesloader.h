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

#include "utils/utils.cpp"

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

    /// Appende le entryes della cartella all' item
    void appendEntries(QTreeWidgetItem *item, QDir dir);
private:
    // Percorso di ricerca del thread
    QString search_path;

    // Lista di stringhe in cui mettere i nomi dei file sorgenti trovati
    QTreeWidget *destination = nullptr;
};

#endif // SOURCESLOADER_H
