/* Autore: cavallo gabriele
 * Fornisce alcune utility per la gestione dei vari costrutti
 * */

#ifndef UTILITES_CPP
#define UTILITES_CPP

#include <QString>
#include <QChar>
#include <QList>
#include <QStringList>
#include <QSysInfo>
#include <QOperatingSystemVersion>
#include <QDebug>

/// Controlla che la stringa string non contenga nessuno dei caratteri specificati
/// \arg string la stringa da controllare
/// \arg not_allowed_chars Lista di caratteri non consentiti
/// \arg error_char Un puntatore alla stringa in cui mettere il carattere che ha dato errore
static bool compare(QString string, QList<QChar> not_allowed_chars, QString *error_char){
    // Ottengo il numero di caratteri della stringa
    unsigned int string_size = string.count();
    // Ottengo il numero di caratteri non consentiti
    unsigned int not_allowed_count = not_allowed_chars.count();

    for(unsigned int x = 0; x < string_size; x++){
        // Confronto il carattere con la lista di caratteri
        for(unsigned int y = 0; y < not_allowed_count; y++){
            if(string[x] == not_allowed_chars[y]){
                // Imposto il carattere di errore
                *error_char = not_allowed_chars[y];
                return false;
            }
        }
    }
    // Imposto il carattere di errore ad una stringa vuota
    *error_char = "";
    return true;
}

/// Formatta il percorso concatenando il percorso base e i percorsi addizionali utilizzando
/// il separatore nativo del sistema operativo
static QString formatPathForOs(QString base, QStringList additions){
    // Versione del sistema operativo ospite
    auto version = QOperatingSystemVersion::current();
    // Carattere da usare come separatore
    QChar separator_for_os;
    if(version >= QOperatingSystemVersion::Windows7){
        // Utilizzo separatori windows
        separator_for_os = '\\';
    }
    else{
        // Utilizzo separatori linux like
        separator_for_os = '/';
    }

    QString path = base;
    for(int x = 0; x < additions.count(); x ++){
        // Aggiungo il separatore
        path += separator_for_os;
        // Aggiungo il percorso
        path += additions[x];
    }

    return path;
}

/// Rimuove tutti gli elementi che indicano percorsi ridondanti
static QStringList removeRedundant(QStringList list){
    QStringList result;
    for(int x = 0; x < list.count(); x++){
        if(list[x] != ".." && list[x] != "."){
            result.append(list[x]);
        }
    }
    return result;
}

static QChar getOSSeparator(){
    // Versione del sistema operativo ospite
    auto version = QOperatingSystemVersion::current();
    // Carattere da usare come separatore
    QChar separator_for_os;
    if(version >= QOperatingSystemVersion::Windows7){
        // Utilizzo separatori windows
        separator_for_os = '\\';
    }
    else{
        // Utilizzo separatori linux like
        separator_for_os = '/';
    }
    return separator_for_os;
}

#endif
