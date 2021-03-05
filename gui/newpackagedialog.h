/*
 * Cavallo Gabriele
 * Dialog for creating new packages in ArduinoPacMan
 * */

#ifndef NEWPACKAGEDIALOG_H
#define NEWPACKAGEDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QChar>
#include <QFileDialog>

#include "utils/utils.h"
#include "settings/settings.h"
#include "settings/key.h"

namespace Ui {
class NewPackageDialog;
}

class NewPackageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPackageDialog(Settings *settings = nullptr, QWidget *parent = nullptr);
    ~NewPackageDialog();

    /**
     * @brief getPackageName returns the name of the package
     * @return
     */
    QString getPackageName();

    /**
     * @brief getPackagePath returns the path of the package
     * @return
     */
    QString getPackagePath();

    /**
     * @brief getSourcesPath Returns the path of the sources for the package
     * @return
     */
    QString getSourcesPath();

    /**
     * @brief getMainFilePath Returns the main source file path
     * @return
     */
    QString getMainFilePath();

    /**
     * @brief getDescription Returns the description of the package
     * @return
     */
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

    // Puntatore al pulsante per andare avanti
    QPushButton *continue_button = nullptr;

    // Impostazioni della applicazione
    Settings *settings = nullptr;

protected:
    void disableContinueWithPathError();
    void disableContinueWithNameError();
    void disableContinueWithSourcesError();

    /// Cerca di abilitare la possibilità di andare avanti
    void enableContinue();
};

#endif // NEWPACKAGEDIALOG_H
