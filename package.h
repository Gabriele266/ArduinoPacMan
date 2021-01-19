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

#include "library.h"
#include "pacman_info.h"
#include "utils.cpp"

class Package
{
public:
    Package();
    Package(QString name);

    /// Imposta il nome del pacchetto
    void setName(QString name);

    /// Restituisce il nome del pacchetto
    QString getName();

    /// Imposta il percorso di salvataggio
    void setSavePath(QString val);

    /// Restiuisce il percorso di salvataggio del pacchetto
    QString getSavePath();

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
    // Nome del pacchetto
    QString name;
    // Percorso di salvataggio del pacchetto
    QString path;
    // Descrizione del pacchetto
    QString description;
    // Array con le librerie
    QList<Library*> libraries;
    // Percorso del file di descrizione del pacchetto
    QString description_path;
};

#endif // PACKAGE_H
