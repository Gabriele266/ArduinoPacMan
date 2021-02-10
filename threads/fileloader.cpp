#include "fileloader.h"

FileLoader::FileLoader()
{

}

void FileLoader::run(){
    if(browser != nullptr){
        // Creo il file
        QFile file(file_path);
        QString buffer = "";

        // Cerco di aprirlo
        if(file.open(QIODevice::ReadOnly)){
            // Creo uno stream di testo
            QTextStream str(&file);

            // Valore della riga corrente
            QString curLine;

            while(!str.atEnd()){
                // Leggo una riga
                curLine = str.readLine();
                buffer += curLine;
            }
            file.close();
            browser->setHtml(buffer);
            qInfo() << "Caricamento del file " << file_path << " completato. " << endl;
        }
        else{
            qInfo() << "Impossibile leggere il file: " << file.errorString() << endl;
            qInfo() << "File ricercato: " << file_path << endl;
        }
    }
}
