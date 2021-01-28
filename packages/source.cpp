#include "source.h"

Source::Source()
{
    file_path = "";
    file_suffix = "";
    source_name = "";
    file = "";
    type = Unknown;
    dependencies.clear();
}

Source::Source(QString f){
    if(file != ""){
        QFileInfo info(f);
        file_path = info.filePath();
        source_name = info.fileName();
        file_suffix = info.suffix();
        file = f;

        if(file_suffix == "h"){
            type = HeaderFile;
        }
        else if(file_suffix == "cpp" || file_suffix == "c"){
            type = ImplementationFile;
        }
        else if(file_suffix == "ino"){
            type = ArduinoSketch;
        }
        else{
            qInfo() << "Trovato file non riconosciuto: " << file << endl;
            type = Unknown;
        }
    }
}

Dependency* Source::getDependency(Natural index){
    if(index < mk(dependencies.count())){
        return dependencies[index];
    }
    return nullptr;
}

bool Source::needsLibrary(QString name){
    for(Natural x = 0; x < mk(dependencies.count()); x++){
        if(dependencies[x]->getLibraryName() == name){
            return true;
        }
    }
    return false;
}

Dependency* Source::getDependency(QString lib_name){
    if(needsLibrary(lib_name)){
        for(Natural x = 0; x < mk(dependencies.count()); x++){
            if(dependencies[x]->getLibraryName() == lib_name){
                return dependencies[x];
            }
        }
    }
    return nullptr;
}

Natural Source::getTotalUnmetDependencies(){
    // Numero di dipendenze non raggiunte
    Natural total = 0;

    for(Natural x = 0; x < mk(dependencies.count()); x++){
        if(!dependencies[x]->isSolved()){
            total ++;
        }
    }
    return total;
}

Source::Source(QFileInfo info){
    file_path = info.filePath();
    file_suffix = info.suffix();
    source_name = info.fileName();
    file = info.absoluteFilePath();
}

bool Source::fileIsSource(QString file){
    // Informazioni sul file
    QFileInfo inf(file);
    // Estensione
    QString suff = inf.suffix();

    // Controllo se è presente nella lista
    return isAnyOfList(suff, sources_extensions);
}

void Source::appendDependency(Dependency *dep){
    dependencies.append(dep);
}

void Source::setCompleteFile(QString f){
    if(f != ""){
        QFileInfo info(f);
        file_path = info.path();
        source_name = info.fileName();
        file_suffix = info.suffix();
        file = f;

        if(file_suffix == "h"){
            type = HeaderFile;
        }
        else if(file_suffix == "cpp" || file_suffix == "c"){
            type = ImplementationFile;
        }
        else if(file_suffix == "ino"){
            type = ArduinoSketch;
        }
        else{
            qInfo() << "Trovato file non riconosciuto: " << file << endl;
            type = Unknown;
        }
    }
}
