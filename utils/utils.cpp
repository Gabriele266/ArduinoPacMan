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

#include "packages/natural.h"

/// Rappresenta un carattere di a capo
#define endl "\n"

/// Rappresenta un file riga in html
#define html_endl "<br>"

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
    // Carattere non accettabile
    QChar not_acceptable_separator;
    // Percorso base
    QString path = base;
    if(version >= QOperatingSystemVersion::Windows7){
        // Utilizzo separatori windows
        separator_for_os = '\\';
        not_acceptable_separator = '/';

    }
    else{
        separator_for_os = '/';
        not_acceptable_separator = '\\';
    }

    // Rimuovo i caratteri non accettabili
    path = path.replace(not_acceptable_separator, separator_for_os);

    for(int x = 0; x < additions.count(); x ++){
        // Aggiungo il separatore
        path += separator_for_os;
        // Aggiungo il percorso togliendo i caratteri non accettabili
        path += additions[x].replace(not_acceptable_separator, separator_for_os);
    }

    qInfo() << "Percorso formattato: " << path << endl;
    return path;
}

/// Determina se la stringa str è presente almeno una volta nella lista list
static bool isAnyOfList(QString str, QStringList list){
    for(Natural x = 0; x < Natural::make(list.count(), ElideUnderZero); x++){
        if(str == list[x]){
            return true;
        }
    }
    return false;
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

/// Controlla che la stringa string non esista nella lista list
/// restituisce true se la situazione è verificata
static bool notExists(QString string, QStringList list){
    for(int x = 0; x < list.count(); x++){
        if(list[x] == string){
            return false;
        }
    }
    return true;
}

/// Restituisce il percorso della home del sistema operativo
/// su linux /home/$username
/// su windows C:\Users\$Username
static QString getHomePath(){
    auto os_vers = QOperatingSystemVersion::currentType();

    // Prendo il nome utente corrente
    QString user_name = qgetenv("USER");
    if(user_name == ""){
        user_name = qgetenv("USERNAME");
    }

    // Controllo se si tratta di windows
    if(os_vers == QOperatingSystemVersion::Windows){
        return "C:\\Users\\" + user_name + "\\";
    }
    else{
        return "/home/" + user_name + "/";
    }
}

/// Risolve un percorso che contiene collegamenti simbolici come ~.
static QString resolvePath(QString startPath){
    if(startPath.startsWith("~")){
        return startPath.replace("~", getHomePath());
    }
    else{
        return startPath;
    }
}

/// Applica una politica di gestione a un numero intero e restituisce il numero naturale
static Natural mk(int num){
    return Natural::make(num, ElideUnderZero);
}

#endif
