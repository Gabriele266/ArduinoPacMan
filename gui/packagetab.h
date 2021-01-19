/*
 * Autore: cavallo gabriele
 * Rappresenta un tab in un gestore di pacchetti per gestirne la visualizzazione
 * */
#ifndef PACKAGETAB_H
#define PACKAGETAB_H

#include <QWidget>
#include <QString>

#include "package.h"

namespace Ui {
class PackageTab;
}

class PackageTab : public QWidget
{
    Q_OBJECT

public:
    explicit PackageTab(Package *package, QWidget *parent = nullptr );
    ~PackageTab();

    /// Imposta i tag del tab
    void setTags(QString tags);

    /// Restituisce i tag relativi al tab
    QString getTags();

    /// Determina se il tab è visibile o no
    bool isVisible() {return opened;}

private:
    Ui::PackageTab *ui;
    // Pacchetto che rappresenta il tab
    Package *package;
    // Tag associato al tab
    QString tag;
    // Indica se il tab è visualizzato o no
    bool opened = true;
};

#endif // PACKAGETAB_H
