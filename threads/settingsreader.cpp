#include "settingsreader.h"

SettingsReader::SettingsReader()
{

}

void SettingsReader::run(){
    // Controllo che siano state messe delle impostazioni
    if(settings != nullptr){
        // File da cui leggere
        QFile f(settings->getFilePath());
        // Cerco di aprirlo
        if(f.open(QIODevice::ReadOnly)){
            // Creo un documento xml
            QDomDocument document;
            document.setContent(&f);

            // Prendo il nodo root
            QDomElement root = document.documentElement();
            settings->setName(root.tagName());
            settings->setDescription(root.attribute("description"));
            settings->setCreationDate(root.attribute("creation-date"));

            // Elementi figlio del root
            QDomNodeList childs = root.childNodes();
            // Scorro tutti i figli dell' elemento root (rappresentano i gruppi di impostazioni)
            for(Natural x = 0; x < mk(childs.count()); x++){
                // Ottengo l'elemento corrente
                QDomElement cur_child = childs.at(x).toElement();
                Group *gr = new Group();
                gr->setName(cur_child.tagName());
                gr->setDescription(cur_child.attribute("info"));

                // Scorro tutti gli elementi figli
                QDomNodeList keys_items = cur_child.childNodes();

                for(Natural y = 0; y < mk(keys_items.count()); y++){
                    QDomElement cur_key = keys_items.at(y).toElement();

                    Key* k = new Key();
                    k->setName(cur_key.tagName());
                    k->setValue(cur_key.attribute("value"));
                    // Prendo i suoi attributi
                    auto attributes_list = cur_key.attributes();
                    for(Natural z = 0; z < mk(attributes_list.count()); z++){
                        QDomAttr i = attributes_list.item(z).toAttr();
                        // Ignoro il nodo value
                        if(i.name() != "value"){
                            Attribute *attr = new Attribute();
                            attr->setName(i.name());
                            attr->setValue(i.value());

                            // Aggiungo l'alltributo alla chiave
                            k->addAttribute(attr);
                        }
                    }

                    // Aggiungo la chiave
                    gr->addKey(k);
                }

                // Aggiungo il gruppo alle impostazioni
                settings->addGroup(gr);
            }
            f.close();
        }
        else{
            qInfo() << "File richiesto non esistente per la lettura delle impostazioni. " << endl;
        }
    }
}
