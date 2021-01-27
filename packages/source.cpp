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
