#include "srcdependencylister.h"

SrcDependencyLister::SrcDependencyLister(Package* pack){
    package = pack;
}

SrcDependencyLister::SrcDependencyLister() : SrcDependencyLister(nullptr)
{
    // Nothing
}

void SrcDependencyLister::appendDependencyToWidget(Dependency *dep){
    // Controllo che esista un controllo
    if(widget != nullptr){
        // Controllo che la dipendenza non sia nulla
        if(dep != nullptr){
            // Controllo che il sorgente corrente esista
            if(current_source != nullptr){
                QTreeWidgetItem *item = new QTreeWidgetItem();
                item->setText(0, dep->getLibraryName());
                item->setText(1, current_source->getName());
                item->setText(2, current_source->getCurrentRow().toString());
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
            else{
                QMessageBox::critical(nullptr, "Errore", "Errore durante l' aggiunta della dipendenza "
                + dep->getLibrary()->getName() + " al sorgente. Il sorgente corrente è nullptr. ");
            }
        }
    }
}

void SrcDependencyLister::processLibraryInclusion(QString header_line){
    // Stringa per contenere il testo dell' header
    QString head = header_line.remove(' ');
    // Ottengo il contenuto delle parentesi angolari
    head = head.mid(head.indexOf('<') + 1, head.indexOf('>'));
    // Tolgo eventuali parentesi angolari rimanenti
    head = head.remove('>');

    // Prendo il nome della libreria
    QStringList div = head.split('.');
    // Controllo se si tratta di un file con estensione o una inclusione in stile c++ senza .h o .cpp
    if(div.count() >= 1){
        // Nome della libreria
        QString lib_name = div[0];

        // Formatto una dipendenza
        Dependency *d = new Dependency();
        d->setLibraryName(lib_name);
        d->setHeaderName(head);
        // Aggiungo la dipendenza al sorgente corrente
        current_source->appendDependency(d);
        // Appendo la dipendenza al controllo
        appendDependencyToWidget(d);
    }
}

void SrcDependencyLister::processLocalFileInclusion(QString line){
    // Contenuto dell' header
    QString head = line.remove(' ');
    head = head.mid(head.indexOf('"') + 1, head.lastIndexOf('"'));
    head = head.remove('"');

    QString complete_path = formatPathForOs(current_path, QStringList(head));
    // Creo un sorgente e avvio la ricerca di dipendenze
    Source* src = new Source();
    src->setCompleteFile(complete_path);
    processSource(src);
}

void SrcDependencyLister::processSource(Source *src){
    // Imposto il file corrente
    current_source = src;
    // Aggiungo il sorgente al pacchetto
    package->addSource(src);
    // Resetto la riga corrente
    src->setCurrentRow(1);
    current_path = src->getFilePath();

    // Creo l'oggetto file per poterlo gestire
    QFile file(src->getCompleteFile());
    // Indica lo stato del commento
    bool comment_state = false;

    if(file.open(QIODevice::ReadOnly)){
        // Creo uno stream di testo
        QTextStream str(&file);

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
                    // Avvio il processo per la inclusione di una libreria
                    processLibraryInclusion(curLine);
                }
                else{
                    processLocalFileInclusion(curLine);
                    // Ripristino il file sorgente corrente
                    current_source = src;
                }
            }
            else{

            }
            src->switchToNextLine();
        }
    }
}

void SrcDependencyLister::run(){
    // Controllo che sia stato impostato un pacchetto a cui aggiungere le dipendenze
    if(package != nullptr){
        // Controllo che il pacchetto abbia un sorgente principale
        if(package->getMainSourcePath() != ""){
            // Parto dal file principale
            Source *src = new Source();
            QString main_file_path = package->getMainSourcePath();
            src->setCompleteFile(main_file_path);
            processSource(src);
        }
    }
}
