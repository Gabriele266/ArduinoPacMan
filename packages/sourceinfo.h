/*  Cavallo Gabriele
 *  Represents methods to have informazions about sources
 * */

#ifndef SOURCEINFO_H
#define SOURCEINFO_H

#include <QString>
#include <QFileInfo>

#include "utils/costants.h"
#include "utils/macros.h"
#include "utils/utils.h"

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

class SourceInfo
{
public:
    SourceInfo();

    /**
     * @brief fileIsSource Checks if this file is a valid source
     * @param file The file to check
     * @return true if it is valid
     */
    static bool fileIsSource(QString file);

    /**
     * @brief sourceTypeToString formats a string starting from a source type value.
     * @param type the type
     * @return the string
     */
    static QString sourceTypeToString(SourceType type);

    /**
     * @brief fileToSourceType Returns the source type of the
     * file starting from it's whole path or only the name with extension
     * @param file the file to use
     * @return the type
     */
    static SourceType fileToSourceType(QString file);
};

#endif // SOURCEINFO_H
