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
    SourcesLister(Source* file, QList<Dependency*>* results);

    void run();

    /// Imposta il sorgente da cui partire alla ricerca delle librerie
    SETTER(Source*, startFile, Source)

    /// Imposta la lista in cui aggiungere i risultati della ricerca
    SETTER(QList<Dependency*>*, resultsList, DestinationList)

    /// Imposta il widget a cui aggiungere i risultati
    SETTER(QTreeWidget*, widget, Widget);

private:
    // File da cui partire
    Source* startFile = nullptr;
    // Lista a cui aggiungere i risultati
    QList<Dependency*> *resultsList = nullptr;
    // Widget a cui aggiungere i risultati
    QTreeWidget *widget = nullptr;

protected:
    // Appende la dipendenza al controllo ad albero specificato
    void appendDependencyToWidget(Dependency *dep);
};

#endif // SOURCESLISTER_H
