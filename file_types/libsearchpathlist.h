/* Autore: cavallo gabriele
 * Rappresenta una lista di percorsi di ricerca delle librerie
 * */

#ifndef LIBSEARCHPATHLIST_H
#define LIBSEARCHPATHLIST_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QThread>
#include <QStringList>

#include "packages/natural.h"

/// Rappresenta una lista di percorsi di ricerca delle librerie
class LibSearchPathList
{
public:
    LibSearchPathList();

    /// Aggiunge un percorso
    void addPath(QString path);

    /// Restituisce il percorso con quell' indice
    QString getPath(Natural index);

    /// Restituisce il numero di percorsi di ricerca
    Natural getListCount();

    /// Controlla che tutti i percorsi esistano
    /// se esistono tutti restituisce true
    bool checkUp();

    /// Imposta il file su cui salvare le informazioni
    void setSavePath(QString path);

    /// Restituisce il percorso di salvataggio delle informazioni
    QString getSavePath();

    /// Rimuove il percorso con quell' indice
    void removePath(Natural index);

    /// Rimuove l'elemento con quel valore di percorso
    /// restituisce vero se lo ha trovato o falso se non esisteva
    bool removeElemByPath(QString path);

    /// Restituisce un puntatore alla lista di elementi
    QStringList* getEntryList();
private:
    // Percorso di salvataggio del file
    QString file_path;
    // Lista con tutti i percorsi
    QStringList pathList;
};

#endif // LIBSEARCHPATHLIST_H
