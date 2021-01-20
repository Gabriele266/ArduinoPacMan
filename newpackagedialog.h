#ifndef NEWPACKAGEDIALOG_H
#define NEWPACKAGEDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QChar>
#include <QFileDialog>

#include "utils/utils.cpp"

namespace Ui {
class NewPackageDialog;
}

class NewPackageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPackageDialog(QWidget *parent = nullptr);
    ~NewPackageDialog();

    /// Restituisce il nome del pacchetto
    QString getPackageName();

    /// Restituisce il percorso del pacchetto
    QString getPackagePath();

    QString getSourcesPath();

    QString getMainFilePath();

private slots:


    void on_packageName_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_packagePath_textChanged(const QString &arg1);

    void on_sfoglia_clicked();

    void on_change_clicked();

    void on_buttonBox_accepted();

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
    /// Cerca di abilitare la possibilità di andare avanti
    void enableContinue();

    // Puntatore al pulsante per andare avanti
    QPushButton *continue_button;
};

#endif // NEWPACKAGEDIALOG_H
