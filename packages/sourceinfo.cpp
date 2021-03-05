#include "sourceinfo.h"

SourceInfo::SourceInfo()
{

}

bool SourceInfo::fileIsSource(QString file){
    // Informazioni sul file
    QFileInfo inf(file);
    // Estensione
    QString suff = inf.suffix();

    // Controllo se è presente nella lista
    return isAnyOfList(suff, sources_extensions);
}

QString SourceInfo::sourceTypeToString(SourceType type){
    switch(type){
    case HeaderFile:
        return "Header";
    case ImplementationFile:
        return "Implementation";
    case ArduinoSketch:
        return "Arduino Sketch";
    default:
        return "No source";
    }
}

SourceType SourceInfo::fileToSourceType(QString file){
    // Get the suffix
    QString s = file.split('.').last();

    if(s == "h" || s == "hpp"){
        return HeaderFile;
    }
    else if(s == "cpp" || s == "c"){
        return ImplementationFile;
    }
    else if(s == "ino"){
        return ArduinoSketch;
    }
    else{
        return Unknown;
    }
}
