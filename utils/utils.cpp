/* Autore: cavallo gabriele
 * Fornisce alcune utility per la gestione dei vari costrutti
 * */

#ifndef UTILITES_CPP
#define UTILITES_CPP

#include "utils.h"

bool compare(QString string, QList<QChar> not_allowed_chars, QString *error_char){
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

QString formatPathForOs(QString base, QStringList additions){
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

    return path;
}

bool isAnyOfList(QString str, QStringList list){
    for(Natural x = 0; x < Natural::make(list.count(), ElideUnderZero); x++){
        if(str == list[x]){
            return true;
        }
    }
    return false;
}

QStringList removeRedundant(QStringList list){
    QStringList result;
    for(int x = 0; x < list.count(); x++){
        if(list[x] != ".." && list[x] != "."){
            result.append(list[x]);
        }
    }
    return result;
}

QString boolToString(bool value, bool yesNoorTrueFalse){
    if(yesNoorTrueFalse){
        // Applico la politica yes/no
        if(value) return "Yes";
        else return "No";
    }
    else{
        if(value) return "True";
        else return "False";
    }
}

QChar getOSSeparator(){
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

QString getParentDir(QString& path){
    // Copia della stringa
    QString result = path;
    QChar s = getOSSeparator();
    // Ottengo l'indice dell' ultimo / o \ del percorso
    int index = path.lastIndexOf(s);

    result.truncate(index);
    return result;
}

bool notExists(QString string, QStringList list){
    for(int x = 0; x < list.count(); x++){
        if(list[x] == string){
            return false;
        }
    }
    return true;
}

QString getHomePath(){
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

QString getCurrentPath(){
    return QDir::currentPath();
}

QString resolvePath(QString startPath){
    // variabile con il risultato delle operazioni
    QString result = startPath;

    if(result.startsWith("$CURPATH$/")){
        result.replace("$CURPATH$", QDir::currentPath());
    }

    if(result.startsWith("$OSHOME$")){
        QChar s = getOSSeparator();
        result.replace(QString("$OSHOME$") + s, getHomePath());
    }

    if(startPath.startsWith("~")){
        result = result.replace("~", getHomePath());
    }

    return result;
}

QString getFileExtension(QString file){
    QStringList split = file.split('.');
    // Controllo se il file ha una estensione
    if(split.count() > 0){
        return split.last();
    }
    else{
        return "";
    }
}

Natural mk(int num){
    return Natural::make(num, ElideUnderZero);
}

QString colorToHtml(QColor &color){
    QString buf = "#";
    buf += QString::number(color.red(), 16);
    buf += QString::number(color.green(), 16);
    buf += QString::number(color.blue(), 16);

    return buf;
}

QColor htmlToColor(QString htmlCode){
    QColor color;
    QString c = htmlCode.remove("#");

    // Conversion status
    bool ok;

    // Check dimensions
    if(c.length() == 6){
        // Convert hex to decimals
        QString r = QChar(c[0]) + c[1];
        color.setRed(r.toInt(&ok, 16));

        QString g = QChar(c[2]) + c[3];
        color.setGreen(g.toInt(&ok, 16));

        QString b = QChar(c[4]) + c[5];
        color.setBlue(b.toInt(&ok, 16));

        return color;
    }
    return QColor();

}

#endif
