/*  Autore: cavallo gabriele
 *  Fornisce metodi di gestione dei file sorgenti
 * */

#ifndef SOURCE_H
#define SOURCE_H

#include <QString>
#include <QList>

#include "dependency.h"
#include "natural.h"
#include "../utils/macros.h"
#include "../utils/utils.cpp"
#include "../utils/costants.h"

/// Rappresenta un tipo di sorgente
enum SourceType{
    /// File di implementazione (.cpp)
    ImplementationFile,
    /// File header (.h)
    HeaderFile,
    /// Scketch di arduino (.ino)
    ArduinoSketch,
    /// Estensione sconosciuta
    Unknown
};

/// Fornisce metodi di gestione dei file sorgenti
class Source
{
public:
    Source();
    Source(QString file);
    Source(QFileInfo info);

    /// Restituisce il percorso relativo del file (senza nome e estensione)
    GETTER(QString, file_path, FilePath)

    /// Restituisce l'estensione del file
    GETTER(QString, file_suffix, FileSuffix)

    /// Restituisce il tipo di sorgente
    GETTER(SourceType, type, SourceType)

    /// Restituisce il numero di dipendenze di questo file
    GETTER(Natural, dependencies.count(), DependenciesCount)

    /// Restituisce la dipendenza con quell' indice, altrimenti nullptr
    Dependency* getDependency(Natural index);

    /// Restituisce la dipendenza che necessita di quella libreria o nullptr
    Dependency* getDependency(QString lib_name);

    /// Aggiunge una dipendenza del file
    void appendDependency(Dependency *dep);

    /// Restituisce una lista con tutte le dipendenze del file
    QList<Dependency*>* getDependenciesList();

    /// Imposta il file del sorgente
    GETTER(QString, file, CompleteFile)

    /// Restituisce il nome del sorgente
    GETTER(QString, source_name, Name)

    /// Imposta il file
    void setCompleteFile(QString file);

    /// Determina se questo file è un sorgente di codice o qualcos' altro
    bool isSource();

    /// Restituisce il numero delle dipendenze che devono ancora essere raggiunte
    Natural getTotalUnmetDependencies();

    /// Determina se questo file è un sorgente di codice o qualcos' altro
    static bool fileIsSource(QString file);

    /// Determina se questo sorgente necessita della libreria name per funzionare
    bool needsLibrary(QString name);
private:
    // Percorso del file
    QString file_path;

    // Estensione del file
    QString file_suffix;

    // Nome del sorgente
    QString source_name;

    QString file;

    // Tipo di sorgente
    SourceType type;

    // Lista di dipendenze del sorgente
    QList<Dependency*> dependencies;
};

#endif // SOURCE_H
