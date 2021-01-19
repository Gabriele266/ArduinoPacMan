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

/// Rappresenta un thread
class SourcesLoader : QThread
{
public:
    SourcesLoader();

    /// Esegue il thread
    void run();

private:
    // Percorso di ricerca del thread
    QString search_path;

    // Lista di stringhe in cui mettere i nomi dei file sorgenti trovati
    QStringList *destination = nullptr;

    // Lista delle estensioni che sono sorgenti
    QStringList sources_suff = {
        "h",
        "cpp",
        "c",
        "hpp",
        "ino"
    };


};

#endif // SOURCESLOADER_H
