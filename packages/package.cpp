#include "package.h"

Package::Package()
{

}

QString Package::getCompletePath(){
    return formatPathForOs(this->path, QStringList(getName()));
}

int Package::getLibraryCount(){
    return libraries.count();
}

bool Package::addLibrary(Library *lib){
    if(lib != nullptr){
        libraries.append(lib);
        return true;
    }
    return false;
}

bool Package::existsLibrary(unsigned int index){
    if(libraries.count() < index && libraries[index] != nullptr){
        return true;
    }
    return false;
}

bool Package::existsLibrary(QString name){
    for(int x = 0; x < libraries.count(); x++){
        if(libraries[x]->getName() == name){
            return true;
        }
    }
    return false;
}

bool Package::existsLibraryWithPath(QString path){
    for(int x = 0; x < libraries.count(); x ++){
        if(libraries[x]->getCompletePath() == path){
            return true;
        }
    }
    return false;
}

Source* Package::getMainSource(){
    for(Natural x = 0; x < mk(sources_list.count()); x++){
        QString y = sources_list[x]->getCompleteFile();
        if(sources_list[x]->getCompleteFile() == main_file){
            return sources_list[x];
        }
    }
    return nullptr;
}

Library* Package::getLibrary(unsigned int index){
    if(existsLibrary(index)){
        return libraries[index];
    }
    return nullptr;
}

void Package::addSource(Source *src){
    if(src != nullptr){
        sources_list.append(src);
    }
}

Source* Package::getSource(Natural index){
    if(index < Natural::make(sources_list.count(), ElideUnderZero)){
        return sources_list[index];
    }
    return nullptr;
}

Source* Package::getSource(QString file){
    // Scorro tutti i sorgenti e controllo se qualcuno ha lo stesso nome
    for(Natural x = 0;  x < mk(sources_list.count()); x++){
        QDir s = sources_list[x]->getCompleteFile();
        if(s == QDir(file)){
            return sources_list[x];
        }
    }
    return nullptr;
}

bool Package::existsSource(QString file){
    if(getSource(file) != nullptr){
        return true;
    }
    return false;
}

bool Package::existsDependency(Dependency *dep){
    if(dep != nullptr){
        // Scorro tutti i file sorgenti
        for(Natural x = 0; x < mk(sources_list.count()); x++){
            Source* current = sources_list[x];

            Dependency *curr_dep = nullptr;
            // Scorro le sue dipendenze
            for(Natural y = 0; y < current->getDependenciesCount(); y++){
                // Prendo la dipendenza corrente
                curr_dep = current->getDependency(y);
                if(curr_dep->getLibraryName() == dep->getLibraryName()){
                    // La dipendenza esiste
                    return true;
                }
            }
        }
    }
    return false;
}

Natural Package::getTotalDependencies(){
    // Numero totale delle dipendenze
    Natural total = 0;

    // Scorro tutti i sorgenti
    for(Natural x = 0; x < mk(sources_list.count()); x++){
        total += sources_list[x]->getDependenciesCount();
    }
    return total;
}

Natural Package::getTotalUnmetDependencies(){
    // Numero totale
    Natural total = 0;

    for(Natural x = 0; x < mk(sources_list.count()); x++){
        total += sources_list[x]->getTotalUnmetDependencies();
    }

    return total;
}

Dependency* Package::getDependency(Source *src, Natural index){
    return src->getDependency(index);
}

Dependency* Package::getDependency(QString library){
    for(Natural x = 0; x < mk(sources_list.count()); x++){
        if(sources_list[x]->needsLibrary(library)){
            return sources_list[x]->getDependency(library);
        }
    }
    return nullptr;
}

bool Package::create(){
    // Creo la cartella per il pacchetto
    QDir dir;
    // Formatto il percorso giusto per il sistema operativo
    QString package_path_complete = formatPathForOs(path, QStringList(getName()));
    qInfo() << "Percorso per os: " << package_path_complete << "\n";
    dir.mkdir(package_path_complete);
    // Creo il file di progetto
    QString package_file = formatPathForOs(package_path_complete, QStringList(getName() + ".pak"));
    QFile file(package_file);

    // Controllo se riesco ad aprirlo
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        // Creo uno stream di testo
        QTextStream str(&file);

        // Creo il documento xml
        QDomDocument doc;

        // Creo l'elemento root
        QDomElement root = doc.createElement("package");
        doc.appendChild(root);

        // Metto un commento per rendere il file leggibile
        root.appendChild(doc.createComment("File di pacchetto per ArduinoPacMan. Contiene le informazioni del pacchetto. "));

        // Metto il nome del pacchetto
        QDomElement elem = doc.createElement("name");
        elem.setAttribute("value", getName());
        root.appendChild(elem);

        // Metto la descrizione
        QDomElement desc = doc.createElement("description");
        desc.setAttribute("value", getDescription());
        root.appendChild(desc);

        // Momento di creazione del pacchetto
        QDomElement creation = doc.createElement("creation_info");
        creation.setAttribute("date", getCreationDate().toString());
        creation.setAttribute("time", getCreationTime().toString());
        root.appendChild(creation);

        // Ultima modifica
        QDomElement last_modify = doc.createElement("modify_info");
        last_modify.setAttribute("date", getLastModifyDate().toString());
        last_modify.setAttribute("time", getLastModifyTime().toString());
        root.appendChild(last_modify);

        QDomElement sources = doc.createElement("sources");
        sources.setAttribute("path", getSourcesPath());
        sources.setAttribute("main_file", getMainSourcePath());
        root.appendChild(sources);

        QDomElement vers = doc.createElement("pac-version");
        vers.appendChild(doc.createTextNode(ARDUINO_PACMAN_VERSION.toString()));
        root.appendChild(vers);

        str << doc.toString();
        str.flush();
        file.close();
        return true;
    }
    else{
        return false;
    }
    return false;
}

