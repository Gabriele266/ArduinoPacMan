#ifndef PACKAGETAB_H
#define PACKAGETAB_H

#include <QWidget>

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

private:
    Ui::PackageTab *ui;
    Package *package;
};

#endif // PACKAGETAB_H
