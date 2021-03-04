/* Autore: cavallo gabriele
 * Rappresenta una libreria
 * */

#ifndef LIBRARY_H
#define LIBRARY_H

// Header qt
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

// Header custom
#include "version.h"
#include "attributeditem.h"
#include "utils/macros.h"
#include "utils/utils.h"

/// Rappresenta una libreria
class Library : public AttributedItem
{
public:
    Library();
    Library(QString name);

    GETTER_SETTERC(QString, path, Path,
                   Imposta il percorso in cui si trova questa libreria,
                   Restituisce il percorso in cui è stata salvata la libreria)

    /// Imposta il percorso in cui si trova la libreria (senza il nome)
    /// \arg dir Istanza della classe dir che punta alla cartella
    CUSTOM_SETTER(QDir, path, Path, mem.path())

    /// Imposta il percorso completo della libreria (percorso e nome)
    void setCompletePath(QString path);

    /// Imposta il nome della cartella che contiene la documentazione della libreria
    /// \arg dir_name Nome della cartella
    void setDocumentationDir(QString dir_name);

    /// Determina se la libreria ha un percorso contenente una documentazione
    /// \return Un istanza di bool
    bool hasDocumentationDir();

    /// Restituisce il nome della cartella della documentazione, se non esiste restituisce -none-
    /// \return Il nome della cartella come stringa
    QString getDocumentationDir();

    /// Restituisce il percorso completo della documentazione
    QString getDocumentationAbsolutePath();

    /// Determina se la libreria ha un file per la colorazione
    bool hasKeywordsFile();

    /// Determina se la libreria ha un file di proprietà
    bool hasPropertiesFile();

    /// Determina se la libreria ha degli esempi integrati
    bool hasExamples();

    /// Inizializza la libreria controllando vari parametri
    /// \return Un indicatore di successo
    bool init();

    /// Restituisce il percorso completo della libreria compreso
    /// di nome
    QString getCompletePath();

private:
    // Percorso
    QString path;
    // Nome della cartella per la documentazione
    QString documentation_dir_name;

    // Indica se la libreria ha un file di proprietà
    bool properties_file = false;

    // Indica se la libreria ha un file di keywords
    bool keywords_file = false;

    // Indica se la libreria ha una cartella con degli esempi
    bool examples_dir = false;

    // Indica se la libreria ha una documentazione
    bool documentation = false;

    // Indica se la libreria ha un file read_me
    bool read_me = false;

    bool has_sources = false;

    // Indica se la libreria ha un file con lo stesso nome da includere
    bool has_include_file = false;

    // Lista con tutte le cartelle che non sono per esempi, documentazione
    QStringList extra_dirs;

    // Lista degli esempi della libreria (nomi dei file)
    QStringList examples_list;

    // Lista con i file sorgente presenti nella libreria
    QStringList sources_list;

    // Versione della libreria
    Version version;
};

/// Carica i sorgenti della libreria nella lista interna
/// \arg base path percorso da cui far partire la ricerca
bool loadSources(QString base_path, QStringList *sources_list);

/// Restituisce una lista con i file presenti nel percorso
void getFilesList(QString path, QStringList *destination);

#endif // LIBRARY_H
