/*
 * Rappresenta un pacchetto nell' ambiente
 */

#ifndef PACKAGE_H
#define PACKAGE_H

#include <QString>
#include <QList>
#include <QDomElement>
#include <QDomDocument>
#include <QDomNode>
#include <QDate>

#include "library.h"
#include "pacman_info.h"
#include "../utils/utils.cpp"
#include "attributeditem.h"
#include "utils/macros.h"

/// Rappresenta un pacchetto
class Package : public AttributedItem
{
public:
    Package();
    Package(QString name);

    GETTER_SETTERC(QString,
                   path, SavePath,
                   Imposta il percorso di salvataggio del pacchetto (senza il nome),
                   Restituisce il percorso in cui è stato salvato il pacchetto (escluso il nome))

    GETTER_SETTERC(QString, sources_path, SourcesPath,
                   Imposta il percorso dei sorgenti legati al progetto,
                   Ottiene il percorso dei sorgenti in uso dal pacchetto)

    GETTER_SETTERC(QString, main_file, MainFilePath,
                   Imposta il percorso completo del file principale del progetto (punto di entrata del codice),
                   Restituisce il percorso completo del file principale del progetto)

    /// Restituisce il percorso completo del progetto (salvataggio + nome)
    QString getCompletePath();

    /// Restituisce il numero di librerie presenti
    int getLibraryCount();

    /// Aggiunge una libreria
    /// \arg lib un puntatore alla libreria da aggiungere
    /// \return true se l'operazione ha avuto successo
    bool addLibrary(Library *lib);

    /// Restituisce la libreria con quell' indice
    /// \arg index numero intero senza segno che rappresenta l'indice della libreria
    /// \return Un puntatore alla libreria o nullptr se non esiste
    Library* getLibrary(unsigned int index);

    /// Determina se esiste una libreria con quell' indice
    /// \arg index indice della libreria
    /// \return true se esiste false se non esiste
    bool existsLibrary(unsigned int index);

    /// Determina se esiste una libreria con quel nome
    /// \arg name nome della libreria
    /// \return true se esiste
    bool existsLibrary(QString name);

    /// Determina se esiste una libreria con quel percorso
    /// \arg path percorso della libreria, incluso il nome
    /// \return true se esiste
    bool existsLibraryWithPath(QString path);

    /// Restituisce un puntatore alla lista delle librerie per effettuare elaborazioni su di esse
    QList<Library*>* getLibrariesList() {return &libraries;}

    /// Crea il pacchetto
    bool create();

private:

    // Percorso di salvataggio del pacchetto
    QString path;
    // Percorso dei sorgenti del progetto
    QString sources_path;
    // Percorso del file principale del progetto
    QString main_file;
    // Array con le librerie
    QList<Library*> libraries;
};

#endif // PACKAGE_H
