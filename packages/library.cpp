#include "library.h"

Library::Library()
{

}

void Library::setDocumentationDir(QString dir_name){
    this->documentation_dir_name = dir_name;

    // Controllo se esiste
    if(QFile::exists(path + "\\" + dir_name)){
        documentation = true;
    }
    else{
        documentation = false;
    }
}

bool Library::hasDocumentationDir(){
    return documentation;
}

QString Library::getDocumentationDir(){
    return documentation_dir_name;
}

QString Library::getCompletePath(){
    return path + "\\" + getName();
}

QString Library::getDocumentationAbsolutePath(){
    if(documentation){
        return path + "\\" + documentation_dir_name;
    }
    else {
        return "";
    }
}

void Library::setCompletePath(QString path){
    QDir dir = path;

    // Controllo se esiste
    if(dir.exists()){
        // Prendo il nome
        setName( dir.dirName());
        dir.cdUp();
        this->path = dir.path();
    }
}

bool Library::hasKeywordsFile(){
    return keywords_file;
}

bool Library::hasExamples(){
    return examples_dir;
}

bool Library::hasPropertiesFile(){
    return properties_file;
}

bool loadSources(QString base_path, QStringList *sources_list){
    QDir dir = base_path;
    QFileInfoList list = dir.entryInfoList();

    // Lista dei file trovati all' interno della cartella
    QStringList files;

    // Funzione ricorsiva
    getFilesList(base_path, &files);

    // Controllo se esiste
    if(dir.exists()){
        // Avvio la ricerca di tutti i file presenti nella cartella
        for(int x = 0; x < files.count(); x ++){
            // Creo un oggetto file
            QFileInfo inf;
            inf.setFile(files[x]);

            if(inf.suffix() == "cpp" || inf.suffix() == "h" || inf.suffix() == "hpp" || inf.suffix() == "c"){
                // Si tratta di un sorgente
                sources_list->append(files[x]);
            }
        }
        return true;
    }
    return false;
}

void getFilesList(QString path, QStringList *destination){
    QDir dir = path;

    // Prendo la lista dei file e delle cartelle
    QFileInfoList lst = dir.entryInfoList();

    for(int x = 0; x < lst.count(); x ++){
        // Controllo se si tratta di un file
        if(lst[x].isFile()){
            destination->append(lst[x].absoluteFilePath());
        }
        else{
            getFilesList(lst[x].path(), destination);
        }
    }
}

bool Library::init(){
    // Controllo che la cartella esista
    QString complete_path = path + "\\" + getName();
    qInfo() << "Percorso completo: " << complete_path << "\n";

    // Creo un oggetto cartella
    QDir dir = complete_path;

    // Controllo se esiste
    if(dir.exists()){
        qInfo() << "Il percorso esiste\n";
        // Controllo se sono presenti dei file
        QFileInfoList inf = dir.entryInfoList();
        if(inf.count() > 0){
            qInfo() << "Sono presenti " << inf.count() << " elementi nella cartella. \n";
            // Sono presenti degli elementi
            // Controllo se esiste un file .h con lo stesso nome
            QString f_name = getName() + ".h";
            qInfo() << "Nome file di include" << f_name << "\n";
            // Scorro gli elementi
            for(int x = 0; x < inf.count(); x++){
                if(inf[x].fileName() == f_name){
                    qInfo() << "Trovato file di include\n";
                    has_include_file = true;
                    has_sources = true;
                }
                else{
                    qInfo() << "Trovato file " << inf[x] << "\n";
                    has_sources = true;
                    // Avvio un thread
                    QFuture<bool> fut = QtConcurrent::run(loadSources, complete_path, &sources_list);
                }
            }

            // Formatto il percorso degli esempi
            QDir examples = formatPathForOs(complete_path, QStringList("examples"));
            qInfo() << "Percorso esempi: " << examples << endl;

            // Controllo se esiste
            if(examples.exists()){
                examples_dir = true;

                // Carico gli esempi nella lista fatta per loro
                QFileInfoList examples_list_int = examples.entryInfoList();
                for(int x = 0; x < examples_list_int.count(); x++){
                    examples_list.append(examples_list_int[x].fileName());
                }
            }

            return true;
        }
        return true;
    }
    return false;
}
