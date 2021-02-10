/*  Autore: cavallo gabriele
 *  Rappresenta un thread di caricamento di un file
 * */

#ifndef FILELOADER_H
#define FILELOADER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QTextBrowser>

#include "utils/macros.h"
#include "utils/utils.cpp"
#include "utils/costants.h"

/// Rappresenta un thread di caricamento di un file
class FileLoader : public QThread
{
public:
    FileLoader();

    GETTER_SETTERC(QTextBrowser*, browser, Browser,
                   Imposta il browser per il testo,
                   Restituisce il browser per il testo)

    GETTER_SETTERC(QString, file_path, FilePath,
                   Imposta il percorso del file,
                   Restituisce il percorso del file)
    void run();
private:
    // File da leggere
    QString file_path = "";
    // Browser per il testo
    QTextBrowser *browser = nullptr;
};

#endif // FILELOADER_H
