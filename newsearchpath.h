#ifndef NEWSEARCHPATH_H
#define NEWSEARCHPATH_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>

#include "utils/utils.cpp"

namespace Ui {
class NewSearchPath;
}

class NewSearchPath : public QDialog
{
    Q_OBJECT

public:
    /// Inizializza il dialogo con un percorso di partenza pari a ""
    explicit NewSearchPath(QString baseValue = "", QWidget *parent = nullptr);

    ~NewSearchPath();

    /// Restituisce il percorso che è stato scelto
    QString getSelectedPath();

private slots:
    void on_buttonBox_accepted();

    void on_pathEditor_textChanged(const QString &arg1);

    void on_editButton_clicked();

private:
    Ui::NewSearchPath *ui;
};

#endif // NEWSEARCHPATH_H
