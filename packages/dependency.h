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
#include "source.h"


/// Rappresenta una dipendenza di un sorgente verso una libreria
class Dependency
{
public:
    Dependency();

    /// Imposta il nome della libreria
    void setLibraryName(QString name);

    /// Imposta il nome dell' header necessario
    void setHeaderName(QString header);

    /// Imposta la versione minimale necessaria
    void setMinimalVersion(Version version);

    /// Imposta il sorgente che ha chiamato questa dipendenza
//    void attachSource(Source *source);

    /// Indica se la dipendenza è raggiunta
    void setSolved(bool val);

    /// Determina se la dipendenza è raggiunta
    bool isSolved();

    /// Imposta la libreria che la raggiunge
    void setLibrary(Library *lib);

    /// Restituisce il nome della libreria
    QString getLibraryName();

    /// Restituisce il valore dell' header richiesto
    QString getHeaderName();

    /// Restituisce la versione minima necessaria al sorgente
    Version getMinimalVersion();

    /// Restituisce la libreria che risolve questa dipendenza o nullptr se non esiste
    Library* getDepLibrary();

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
