/* Autore: cavallo gabriele
 * Rappresenta un thread per la scrittura di una lista di percorsi di ricerca
 * */

#ifndef SEARCHPATHLISTREADER_H
#define SEARCHPATHLISTREADER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QThread>

#include "../settings/libsearchpathlist.h"
#include "../utils/utils.h"

/// Rappresenta un thread per la scrittura di una lista di percorsi di ricerca
class SearchPathListReader : public QThread
{
public:
    SearchPathListReader();

    /// Imposta la lista di destinazione in cui caricare i risultati trovati
    void setDestinationList(LibSearchPathList *list);

    /// File da cui leggere il contenuto
    void setFile(QString file);

    /// Esegue il thread
    void run();
private:
    // Lista in cui caricare i risultati
    LibSearchPathList *list = nullptr;
    // File da cui leggere
    QString file_path;
};

#endif // SEARCHPATHLISTREADER_H
