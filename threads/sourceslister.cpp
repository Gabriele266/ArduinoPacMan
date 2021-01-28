#include "sourceslister.h"

SourcesLister::SourcesLister(Source* file, QList<Dependency*>* results){
    startFile = file;
    resultsList = results;
}

SourcesLister::SourcesLister() : SourcesLister(nullptr, nullptr)
{
    // Nothing
}

void SourcesLister::appendDependencyToWidget(Source *src, Dependency *dep, Natural row){
    // Controllo che esista un controllo
    if(widget != nullptr){
        if(dep != nullptr){
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0, dep->getLibraryName());
            item->setText(1, src->getName());
            item->setText(2, row.toString());
            item->setText(3, "No");
            item->setIcon(0, QIcon(":/icons/browsing/dependencies.png"));
            item->setIcon(3, QIcon(":/icons/browsing/browsing/wrong.png"));
            if(parent != nullptr){
                parent->addChild(item);
            }
            else{
                widget->addTopLevelItem(item);
            }
        }
    }
}

void SourcesLister::run(){
    // Creo l'oggetto file
    QFile file(startFile->getCompleteFile());
    // Indica lo stato del commento
    bool comment_state = false;

    if(file.open(QIODevice::ReadOnly)){
        // Creo uno stream di testo
        QTextStream str(&file);
        // Contatore del numero di riga corrente
        Natural current_row = 0;

        // Processo riga per riga
        while(!str.atEnd()){
            // Leggo la riga corrente
            QString curLine = str.readLine();
            // Controllo se si tratta di una direttiva al preprocessore per una inclusione di libreria
            if(curLine.startsWith("//")){
                comment_state = true;
            }
            else if(curLine.contains("/*")){
                if(!curLine.contains("*/")){
                    comment_state = true;
                }
                else{
                    comment_state = false;
                }
            }
            else if(curLine.contains("*/")){
                comment_state = false;
            }
            else if(curLine.startsWith("#include") && !comment_state){
                // Prendo il contenuto dell' header richiesto
                // Controllo se si tratta di una inclusione globale o di un file locale
                if(curLine.contains('<')){
                    QString head = curLine.mid(curLine.indexOf('<') + 1, curLine.indexOf('>') - 1);
                    // Rimuovo gli spazi
                    head = head.remove('>');
                    qInfo() << "Header richiesto: " << head;
                    // Prendo il nome della libreria
                    QStringList div = head.split('.');
                    if(div.count() == 2){
                        QString lib_name = div[0];

                        // Formatto una dipendenza
                        Dependency *d = new Dependency();
                        d->setLibraryName(lib_name);
                        d->setHeaderName(head);
                        // Aggiungo la dipendenza alla lista
                        resultsList->append(d);
                        // Aggiungo la dipendenza al sorgente
                        startFile->appendDependency(d);
                        // Appendo al controllo
                        appendDependencyToWidget(startFile, d, current_row);
                    }
                }
                else{
                    qInfo() << "Inclusione locale non ancora supportata. " << endl;
                }
            }
            current_row ++;
        }
    }
}
