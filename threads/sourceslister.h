/*  Autore: cavallo gabriele
 *  Rappresenta un thread per il caricamento in una lista delle librerie necessarie ai sorgenti
 * */

#ifndef SOURCESLISTER_H
#define SOURCESLISTER_H

#include <QThread>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QDir>
#include <QTextStream>
#include <QList>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "utils/macros.h"
#include "../packages/dependency.h"
#include "../packages/natural.h"
#include "../packages/source.h"

class SourcesLister : public QThread
{
public:
    SourcesLister();
    SourcesLister(Source* file);

    void run();

    /// Imposta il sorgente da cui partire alla ricerca delle librerie
    SETTER(Source*, startFile, Source)

    /// Imposta il widget a cui aggiungere i risultati
    SETTER(QTreeWidget*, widget, Widget);

    /// Imposta l'oggetto parente a cui aggiungere il controllo
    SETTER(QTreeWidgetItem*, parent, ParentItem)
private:
    // File da cui partire
    Source* startFile = nullptr;
    // Widget a cui aggiungere i risultati
    QTreeWidget *widget = nullptr;
    // Elemento a cui aggiungere i risultati
    QTreeWidgetItem *parent = nullptr;
protected:
    // Appende la dipendenza al controllo ad albero specificato
    void appendDependencyToWidget(Source *src, Dependency *dep, Natural row);
};

#endif // SOURCESLISTER_H
