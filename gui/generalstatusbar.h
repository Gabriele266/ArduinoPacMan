/* Autore: cavallo gabriele
 * Rappresenta un widget per gestire la barra di stato del programma
 *
 * */

#ifndef GENERALSTATUSBAR_H
#define GENERALSTATUSBAR_H

#include <QWidget>
#include <QString>

#include "../packages/package.h"
#include "../packages/library.h"

namespace Ui {
class GeneralStatusBar;
}

class GeneralStatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralStatusBar(QWidget *parent = nullptr);
    ~GeneralStatusBar();

    /// Imposta il nuemro di librerie
    void setLibraryCount(unsigned int count);

    /// Imposta il percorso del pacchetto corrente
    void setCurrentPackagePath(QString path);

    /// Imposta il nuemro di pacchetti aperti
    void setPackagesCount(unsigned int val);
private:
    Ui::GeneralStatusBar *ui;
};

#endif // GENERALSTATUSBAR_H
