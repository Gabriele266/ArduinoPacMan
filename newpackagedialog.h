#ifndef NEWPACKAGEDIALOG_H
#define NEWPACKAGEDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QChar>
#include <QFileDialog>

#include "utils/utils.cpp"
#include "file_types/settings.h"
#include "file_types/key.h"

namespace Ui {
class NewPackageDialog;
}

class NewPackageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPackageDialog(Settings *settings = nullptr, QWidget *parent = nullptr);
    ~NewPackageDialog();

    /// Restituisce il nome del pacchetto
    QString getPackageName();

    /// Restituisce il percorso del pacchetto
    QString getPackagePath();

    /// Restituisce il percorso di tutti i sorgenti del pacchetto
    QString getSourcesPath();

    /// Restituisce il file principale del pacchetto
    QString getMainFilePath();

    /// Restituisce la descrizione del pacchetto
    QString getDescription();

private slots:


    void on_packageName_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_packagePath_textChanged(const QString &arg1);

    void on_sfoglia_clicked();

    void on_change_clicked();

    void on_buttonBox_accepted();

    void on_mainFile_textChanged(const QString &arg1);

private:
    Ui::NewPackageDialog *ui;
    // Lista dei caratteri non accettabili
    QList<QChar> no_chars;
    // Box messaggio di errore
    QMessageBox *error_box = new QMessageBox(this);
    // Indica se è possibile continuare
    bool possible = false;

    // Indica che nel nome sono presenti errori
    bool name_errors = true;
    // Indica che nel percorso sono presenti errori
    bool path_errors = true;

    /// Cerca di disabilitare la possibilità di andare avanti
    void disableContinueWithPathError();

    void disableContinueWithNameError();

    void disableContinueWithSourcesError();

    /// Cerca di abilitare la possibilità di andare avanti
    void enableContinue();

    // Puntatore al pulsante per andare avanti
    QPushButton *continue_button;

    // Impostazioni della applicazione
    Settings *settings = nullptr;
};

#endif // NEWPACKAGEDIALOG_H
