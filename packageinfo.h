/*  Gabriele Cavallo
 *  Rappresenta un dialogo per visualizzare le informazioni di un pacchetto
 * */

#ifndef PACKAGEINFO_H
#define PACKAGEINFO_H

#include <QDialog>
#include <QString>

#include "packages/package.h"
#include "packages/natural.h"
#include "settings/settings.h"

namespace Ui {
class PackageInfo;
}

class PackageInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PackageInfo(Package* package, QWidget *parent = nullptr);

    /// Indica al dialogo di usare queste impostazioni
    void useSettings(Settings *settings) {this->settings = settings;}

    ~PackageInfo();

private:
    Ui::PackageInfo *ui;

    // Pacchetto da usare
    Package *package = nullptr;

    // Impostazioni da usare
    Settings* settings = nullptr;

protected:
    /// Carica il pacchetto
    void loadPackage(Package* package);
};

#endif // PACKAGEINFO_H
