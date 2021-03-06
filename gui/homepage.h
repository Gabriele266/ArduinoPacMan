#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QString>
#include <QMessageBox>

#include "threads/fileloader.h"
#include "utils/utils.h"
#include "tab.h"

namespace Ui {
class HomePage;
}

class HomePage : public QWidget, public Tab
{
    Q_OBJECT

public:
    explicit HomePage(QStringList *recentFiles, QWidget *parent = nullptr);
    ~HomePage();

signals:
    /// Emesso quando si richiede la creazione di un nuovo pacchetto
    void newPackageRequired();

    /// Emesso quando si richiede l'apertura di un nuovo pacchetto
    void openPackageRequired();

private slots:
    void on_newPackage_clicked();

    void on_openPackage_clicked();

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
