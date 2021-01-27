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

Library* Package::getLibrary(unsigned int index){
    if(existsLibrary(index)){
        return libraries[index];
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
        sources.setAttribute("main_file", getMainFilePath());
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

