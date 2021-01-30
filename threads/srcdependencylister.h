/*  Autore: cavallo gabriele
 *  Rappresenta un thread per il caricamento in una lista delle librerie necessarie ai sorgenti
 * */

#ifndef SrcDependencyLister_H
#define SrcDependencyLister_H

#include <QThread>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QDir>
#include <QTextStream>
#include <QList>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>

#include "utils/macros.h"
#include "../packages/dependency.h"
#include "../packages/package.h"
#include "../packages/natural.h"
#include "../packages/source.h"

class SrcDependencyLister : public QThread
{
public:
    SrcDependencyLister();
    SrcDependencyLister(Package* pack);

    void run();

    /// Imposta il pacchetto per cui visualizzare la lista delle dipendenze
    SETTER(Package*, package, Package)

    /// Imposta il widget a cui aggiungere i risultati
    SETTER(QTreeWidget*, widget, Widget);

    /// Imposta l'oggetto parente a cui aggiungere il controllo
    SETTER(QTreeWidgetItem*, parent, ParentItem)

private:
    // File da cui partire
    Package* package = nullptr;
    // Widget a cui aggiungere i risultati
    QTreeWidget *widget = nullptr;
    // Elemento a cui aggiungere i risultati
    QTreeWidgetItem *parent = nullptr;

protected:
    // Appende la dipendenza al controllo ad albero specificato
    void appendDependencyToWidget(Dependency *dep);
    // Processa una inclusione di libreria
    void processLibraryInclusion(QString header_line);
    // Processa una inclusione di un file locale
    void processLocalFileInclusion(QString header_line);
    // Processa un file sorgente
    void processSource(Source *src);

    // Sorgente su cui si sta lavorando
    Source* current_source = nullptr;
    // Percorso corrente della ricerca
    QString current_path = "";
};

#endif // SrcDependencyLister_H
