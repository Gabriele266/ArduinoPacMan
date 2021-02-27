#ifndef UTILS_H
#define UTILS_H

/*  Cavallo Gabriele
 *  Contiene funzioni utili per la gestione dei vari costrutti
 * */

#include <QString>
#include <QChar>
#include <QList>
#include <QStringList>
#include <QSysInfo>
#include <QOperatingSystemVersion>
#include <QDebug>
#include <QDir>

#include "packages/natural.h"

/// Rappresenta un carattere di a capo
#define endl "\n"

/// Rappresenta un file riga in html
#define html_endl "<br>"

/**
 * @brief compare Controlla che la lista di caratteri non sia presente nella stringa e restiuisce il risultato del controllo
 * @param string La stringa da controllare
 * @param not_allowed_chars Lista di QChar che non sono ammessi
 * @param error_char Puntatore alla stringa in cui mettere il carattere che ha dato errore (se esiste)
 * @return true se nella stringa non esiste nessuno di quei caratteri
 */
bool compare(QString string, QList<QChar> not_allowed_chars, QString *error_char);

/**
 * @brief formatPathForOs Formatta un percorso composto da una base e una serie di cartelle / file da aggiungere utilizzando
 * il separatore nativo del sistema operativo.
 * @param base Il percorso base (tutti i separatori vengono convertiti in quelli nativi del sistema operativo. )
 * @param additions Lista di stringhe rappresentanti cartelle o file da aggiungere al percorso tramite concatenazione
 * @return Il percorso formattato
 */
QString formatPathForOs(QString base, QStringList additions);

/**
 * @brief isAnyOfList determina se la stringa è presente almeno una volta in una lista di altre stringhe
 * @param str La stringa da ricercare
 * @param list La lista in cui ricercarla
 * @return true se la stringa viene trovata.
 */
bool isAnyOfList(QString str, QStringList list);

/**
 * @brief removeRedundant Rimuove tutti i percorsi ridondanti nella lista di percorsi
 * @param list Lista di stringhe che rappresentano i percorsi
 * @return Una lista senza i percorsi ridondanti
 */
QStringList removeRedundant(QStringList list);

/**
 * @brief boolToString Converte il valore booleano in una stringa applicando una politica precisa.
 * @param value Valore da convertire in stringa
 * @param yesNoorTrueFalse specifica se utilizzare una notazione di tipo Si/No o Vero/Falso
 * @return La stringa formattata
 */
QString boolToString(bool value, bool yesNoorTrueFalse);

/**
 * @brief getOSSeparator Restituisce il separatore nativo utilizzato dal sistema operativo
 * @return ..
 */
QChar getOSSeparator();

/**
 * @brief getParentDir Restituisce il percorso che contiene la cartella indicata.
 * @param path Il percorso della cartella
 * @return Il percorso padre
 */
QString getParentDir(QString& path);

/**
 * @brief notExists controlla che la stringa non esista nella lista
 * @param string stringa che non deve esistere
 * @param list Lista in cui ricercare
 * @return true se la stringa non esiste
 */
bool notExists(QString string, QStringList list);

/**
 * @brief getHomePath restituisce il percorso della home del sistema operativo
 * @return
 */
QString getHomePath();

/**
 * @brief getCurrentPath Restituisce il percorso corrente
 * @return
 */
QString getCurrentPath();

/**
 * @brief resolvePath Calcola il percorso non simbolico rappresentato dalla stringa, sostituendo eventuali caratteri come ~
 * o variabili utilizzate nelle impostazioni come $CURPATH$ etc
 * @param startPath Percorso da risolvere
 * @return percorso risolto e completo
 */
QString resolvePath(QString startPath);

/**
 * @brief mk crea un numero naturale applicando una politica elideunderzero
 * @param num il numero intero da convertire
 * @return il numero convertito
 */
Natural mk(int num);

#endif // UTILS_H
