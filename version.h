/* Autore: cavallo gabriele
 * Rappresenta una versione come unione di 3 numeri e fornisce funzioni per la sua gestione
 * */

#ifndef VERSION_H
#define VERSION_H

#include <QString>
#include <QStringList>

/// Rappresenta i differenti risultati di una operazione di compare tra due versioni
enum CompareResult{
    /// Indica che le due versioni sono uguali
    Equal,
    /// Indica che la prima versione è successiva alla seconda
    Major,
    /// Indica che la prima versione è precedente alla seconda
    Minor,
    /// Indica un errore nel controllo
    Error
};

/// Rappresenta una versione nel formato 1.0.4, fornendo funzioni per accedervi e per gestirla
class Version
{
public:
    /// Inizializza la versione a 0.0.0
    Version();

    /// Permette di inizializzare una versione dando 3 valori iniziali
    /// \arg m numero della versione maggiore
    /// \arg s numero della sottoversione
    /// \arg r numero della revisione
    Version(unsigned int m, unsigned int s, unsigned int r);

    /// Imposta il valore maggiore della versione
    /// \arg v un numero intero senza segno
    void setMajor(unsigned int v);

    /// Imposta il sottovalore della versione
    /// \arg v un numero senza segno
    void setSub(unsigned int v);

    /// Imposta la revisione della versione
    /// \arg v un numero senza segno
    void setRev(unsigned int v);

    /// Imposta tutti i valori della versione
    void set(unsigned int m, unsigned int s, unsigned int r);

    /// Formatta una stringa con la versione e la restiuisce
    /// \return La stringa formattata
    QString toString();

    /// Effettua un confronto tra questa versione e una specificata.
    /// \arg ver un puntatore ad una classe versione
    /// \return Un valore intero della enumerazione compareresult
    CompareResult compareVersions(Version *ver);

    /// Ricerca una versione a partire da una stringa
    /// \arg version_id stringa contenente la versione nel formato 1.2.0
    bool parseFromString(QString version_id);

    /// Crea una istanza della classe versione a partire da una stringa
    /// \arg Stringa contenente la versione nel formato 1.2.3
    /// \return Una istanza della classe versione con i valori impostati. (in caso di errore la versione sarà 0.0.0
    static Version versionFromString(QString version_id);

    /// Restituisce il numero della versione maggiore
    unsigned int getMajor();

    /// Restituisce il numero della sottoversione
    unsigned int getSub();

    /// Restituisce il numero della revisione
    unsigned int getRev();
private:
    // Valore maggiore
    unsigned int major = 0;

    // Sottoversione
    unsigned int sub = 0;

    // Revisione
    unsigned int rev = 0;
};

#endif // VERSION_H
