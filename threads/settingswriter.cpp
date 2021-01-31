#include "settingswriter.h"

SettingsWriter::SettingsWriter()
{

}

void SettingsWriter::run(){
    if(settings != nullptr){
        // Percorso del file
        QString file_name = settings->getFilePath();
        // Creo il file
        QFile f(file_name);
        // Controllo se riesco ad aprire il file
        if(f.open(QIODevice::WriteOnly | QIODevice::Text)){
            // Creo il documento xml
            QDomDocument document ("settings");
            // Elemento root
            // Formatto l'elemento root per le informazioni generali sulle impostazioni
            QDomElement root = document.createElement(settings->getName());
            root.setAttribute("description", settings->getDescription());
            root.setAttribute("creation-date", settings->getCreationDateString());

            // Aggiungo l'elemento root
            document.appendChild(root);

            // Ottengo gli elementi per tutti i gruppi delle impostazioni
            for(Natural x = 0; x < mk(settings->getGroupsCount()); x++){
                // Prendo il gruppo corrente
                Group* cur = settings->getGroup(x);
                // Controllo che esista
                if(cur != nullptr){
                    QDomElement item = document.createElement(cur->getName());
                    item.setAttribute("info", cur->getDescription());

                    // Scorro tutte le sue chiavi
                    for(Natural y = 0; y < mk(cur->getKeysCount()); y++){
                        // Prendo la chiave corrente
                        Key* cur_key = cur->getKey(y);
                        if(cur_key != nullptr){
                            QDomElement el = document.createElement(cur_key->getName());
                            el.setAttribute("value", cur_key->getValue());

                            // Scorro i suoi attributi
                            for(Natural z = 0; z < mk(cur_key->getAttributesCount()); z++){
                                el.setAttribute(cur_key->getAttributeByIndex(z)->getName(), cur_key->getAttributeByIndex(z)->getValue());
                            }
                            item.appendChild(el);
                        }
                    }
                    root.appendChild(item);
                }

            }

            // Scrivo sul file
            QTextStream str(&f);
            QString s = document.toString();
            str << s;
            str.flush();
            f.close();
        }
        else{
            // Mostro l'errore che è avvenuto
            qInfo() << f.errorString() << endl;
            // Invio un messaggio di errore
            QMessageBox::critical(nullptr, "Errore", QString("Impossibile scrivere le impostazioni %1 nel file %2. Errore restituito: %3")
                                  .arg(settings->getName())
                                  .arg(settings->getFilePath())
                                       .arg(f.errorString()));
        }
    }
}
