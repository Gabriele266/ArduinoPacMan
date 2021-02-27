/* Autore: cavallo gabriele
 * Rappresenta un thread per scrivere una lista di percorsi di ricerca su un file
 * */

#ifndef SEARCHPATHLISTWRITER_H
#define SEARCHPATHLISTWRITER_H

#include <QThread>
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include "../settings/libsearchpathlist.h"
#include "../packages/natural.h"
#include "../utils/utils.h"

/// Rappresenta lo stato di uscita della operazione di scrittura sul file
enum LibWritingEnd{
    NoListPassed,
    FileAccessError,
    PassedPathNotExisting,
    LibrarySearchPathEmpty,
    Success
};

/// Rappresenta un thread per scrivere una lista di percorsi di ricerca su un file
class SearchPathListWriter : public QThread
{
public:
    SearchPathListWriter();

    /// Imposta la lista di percorsi di ricerca da scrivere
    void setLibraryList(LibSearchPathList *info);

    /// Esegue il thread
    void run();

private:
    // Lista di percorsi da scrivere
    LibSearchPathList *searchPathList = nullptr;
};

#endif // SEARCHPATHLISTWRITER_H
