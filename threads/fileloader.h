/*  Autore: cavallo gabriele
 *  Rappresenta un thread di caricamento di un file
 * */

#ifndef FILELOADER_H
#define FILELOADER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QTextBrowser>

#include "utils/macros.h"
#include "utils/utils.h"
#include "utils/costants.h"

/**
 * @brief The FileLoaderExit enum represents the result of the file loading operations
 */
enum FileLoaderExit{
    // Status is not defined yet
    NotStarted,
    // The file wasn't found on the disk
    FileNotFound,
    // No file was mentioned for the input stream
    FileNotSpecified,
    // You do not have the authorizations of opening this file
    AccessDenied,
    // Error during opening the file
    FileOpenError,
    // Success
    Success
};

/// Rappresenta un thread di caricamento di un file
class FileLoader : public QThread
{
public:
    FileLoader();
    FileLoader(QString &file);

    GETTER_SETTERC(QString, file_path, FilePath,
                   Imposta il percorso del file,
                   Restituisce il percorso del file)

    /**
      @brief Returns the file buffer with all the contents of it.
    */
    GETTER(QString&, buffer, FileBuffer)

    /**
      @brief Returns the error string that has been generated after the IO operations.
    */
    GETTER(QString, error_string, ErrorString)

    /**
      @brief Returns the exit result state that has been generated after the IO operations
    */
    GETTER(FileLoaderExit, exit_state, ExitState)

    void run();

    /**
     * @brief wasSuccessFull Determinates if the read operations were successful
     * @return true if they were
     */
    bool wasSuccessful();

    /**
     * @brief exitStateToString Converts a value from the enumeration FileLoaderExit to a string
     * @param exit The value to convert
     * @return The generated text.
     */
    static QString exitStateToString(FileLoaderExit exit);

private:
    // File to read
    QString file_path = "";
    // Thread exit state
    FileLoaderExit exit_state = NotStarted;
    // Error string given in case of errors opening the file
    QString error_string = "";
    // Buffer for the file contents
    QString buffer;
};

#endif // FILELOADER_H
