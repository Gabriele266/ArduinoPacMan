#include "packagereader.h"

PackageReader::PackageReader()
{

}

void PackageReader::run(){
    // Controllo se il percorso specificato esiste
    QDir dir(path);

    if(dir.exists()){
        // Posso continuare
        // Prendo il nome della cartella
        QString package_name = dir.dirName();

        // Imposto il nome del pacchetto
        package->setName(package_name);

        // Formatto il percorso del file di pacchetto
        QString pack_file = formatPathForOs(path, QStringList(package_name + ".pak"));

        // Creo il documento dom per la gestione dell' xml
        QDomDocument document;

        // Oggetto file di pacchetto
        QFile package_file (pack_file);

        // Tento di aprirlo
        if(package_file.open(QIODevice::ReadOnly)){
            // Imposto il contenuto del documento
            document.setContent(&package_file);

            // elemento root
            QDomElement root = document.firstChildElement();

            // Prendo la descrizione del pacchetto
            QDomElement description = root.firstChildElement("description");
            package->setDescription(description.attribute("value"));

            // Prendo la data di creazione del pacchetto
            QDomElement creation_info = root.firstChildElement("creation_info");
            package->setCreationDate(creation_info.attribute("date"));

            // Prendo l orario di creazione
            package->setCreationTime(creation_info.attribute("time"));

            QDomElement modify_info = root.firstChildElement("modify_info");
            package->setLastModifyDate(modify_info.attribute("date"));
            package->setLastModifyTime(modify_info.attribute("time"));

            QDomElement sources = root.firstChildElement("sources");
            package->setSourcesPath(sources.attribute("path"));
            package->setMainFilePath(sources.attribute("main_file"));
        }
    }
}
