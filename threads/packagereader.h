/*  Autore: cavallo gabriele
 *  Rappresenta un thread per la lettura di un pacchetto dal file system
 * */


#ifndef PACKAGEREADER_H
#define PACKAGEREADER_H

#include <QString>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

#include "packages/package.h"
#include "utils/utils.cpp"
#include "utils/macros.h"

/// Rappresenta un thread di lettura di un pacchetto dal file system
class PackageReader : public QThread
{
public:
    PackageReader();

    /// Esegue il thread
    void run();

    /// Imposta il percorso da cui caricare il pacchetto
    SETTER(QString, path, Path);

    /// Restituisce il pacchetto creato da thread
    GETTER(Package*, package, Package)

private:
    // File da cui leggere i contenuti
    QString path;

    // Pacchetto letto dal file system
    Package *package = new Package();
};

#endif // PACKAGEREADER_H
