#ifndef SOURCE_H
#define SOURCE_H

#include <QString>
#include <QList>

#include "dependency.h"
#include "natural.h"

enum SourceType{
    ImplementationFile,
    HeaderFile,
    ArduinoSketch
};


class Source
{
public:
    Source();

private:
    // Percorso del file
    QString filePath;

    // Lista di dipendenze
//    QList<Dependency*> dependencies;

};

#endif // SOURCE_H
