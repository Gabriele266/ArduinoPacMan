/* Autore: cavallo gabriele
 * Rappresenta una dipendenza di un sorgente verso una libreria
 *
 * */

#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include <QString>
#include <QStringList>
#include <QProperty>

#include "library.h"
#include "version.h"

#include "utils/macros.h"


/// Rappresenta una dipendenza di un sorgente verso una libreria
class Dependency
{
public:
    Dependency();
    Dependency(QString libraryName);
    Dependency(QString libraryName, QString header, Version minimal = Version::baseVersion());

    GETTER_SETTERC(QString, libraryName, LibraryName,
                   Imposta il nome della libreria da ricercare,
                   Restituisce il nome della libreria necessaria)

    GETTER_SETTERC(QString, header_name, HeaderName,
                   Imposta il valore dell header ricercato,
                   Restituisce il valore dell header da ricercare)

    GETTER_SETTERC(Version, minimal_version, MinimalVersion,
                   Imposta la versione minima necessaria per il funzionamento,
                   Restituisce la versione minima necessaria alla libreria)

    /// Determina se la dipendenza è raggiunta
    bool isSolved() {return solved;}

    /// Restituisce un puntatore alla libreria che raggiunge questa dipendenza
    /// se non esiste restituisce nullptr
    GETTER(Library*, foundLib, Library)

    /// Crea una dipendenza di una certa libreria da un sorgente
    /// \arg lib_name Nome della libreria da ricercare
    /// \arg lib_header il contenuto della istruzione di inclusione (file da cercare)
    /// \arg minimal versione minima della libreria
    /// \return Una istanza della classe depencency
    static Dependency createDependency(QString lib_name, QString lib_header, Version minimal = Version::baseVersion());

    /// Chiude la dipendenza (la contrassegna come raggiunta) e imposta la libreria lib
    void closeDependency(Library *lib);

private:
    // Nome della libreria necessaria
    QString libraryName;

    // Nome dell' header (in caso di librerie con nome diverso dal file di inclusione)
    QString header_name;

    // Versione minima richiesta
    Version minimal_version;

    // Indica se la dipendenza è stata risolta
    bool solved = false;

    // Libreria che è stata trovata
    Library *foundLib = nullptr;
};

#endif // DEPENDENCY_H
