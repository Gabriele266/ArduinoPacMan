#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <QString>
#include <QException>

#include "utils/macros.h"
#include "packages/natural.h"

using namespace std;

class FileNotFoundException : public QException
{
public:
    FileNotFoundException();
    FileNotFoundException(QString file, QString operation_info = "Loading file");
    FileNotFoundException(QString file, QString operation, Natural line, QString call_file);
    /**
     * @brief toString Returns the exception informations in a string
     * @return
     */
    QString toString();

    GETTER(QString, file, File);
    GETTER(QString, operation_info, OperationInfo);
    GETTER(Natural, line, Line);

    GETTER(QString, callFile, ExceptionFile);

    // Reimplemented functions
    void raise() const override {throw *this;}
    FileNotFoundException *clone() const override {return new FileNotFoundException(*this);}
private:
    // File to search
    QString file;
    // Operation informations
    QString operation_info;
    // Line
    Natural line;
    // File that needs this file
    QString callFile;
};

#endif // FILENOTFOUNDEXCEPTION_H
