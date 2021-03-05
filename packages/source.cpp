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
    if(f != ""){
        QFileInfo info(f);
        file_path = info.filePath();
        source_name = info.fileName();
        file_suffix = info.suffix();
        file = f;

        // Get the type
        type = SourceInfo::fileToSourceType(f);
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

bool Source::isSource(){
    if(getSourceType() != Unknown){
        return true;
    }
    return false;
}

void Source::switchToNextLine(){
    current_row ++;
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

        // Get the source type
        type = SourceInfo::fileToSourceType(f);
    }
}
