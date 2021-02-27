#include "newsearchpath.h"
#include "ui_newsearchpath.h"

NewSearchPath::NewSearchPath(QString basePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSearchPath)
{
    ui->setupUi(this);

    // Imposto il titolo della finestra
    setWindowTitle("Nuovo percorso di ricerca librerie");

    // Imposto il percorso di partenza
    ui->pathEditor->setText(basePath);
}

NewSearchPath::~NewSearchPath()
{
    delete ui;
}

void NewSearchPath::on_buttonBox_accepted()
{
}

QString NewSearchPath::getSelectedPath(){
    return ui->pathEditor->text();
}

void NewSearchPath::on_pathEditor_textChanged(const QString &arg1)
{
    // Controllo che non sia vuoto
    if(arg1 != ""){
        if(QDir(arg1).exists()){
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }
        else{
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    }
}

void NewSearchPath::on_editButton_clicked()
{
    // Testo presente nella casella di impostazione
    QString pt = ui->pathEditor->text();

    // Percorso scelto dall' utente
    QString path;

    // Controllo se è stato messo un percorso base
    if(pt != ""){
        path = QFileDialog::getExistingDirectory(this, "Seleziona un percorso in cui cercare le librerie", pt);
    }
    else{
        path = QFileDialog::getExistingDirectory(this, "Seleziona un percorso in cui cercare le librerie", getHomePath());
    }

    if(path != ""){
        ui->pathEditor->setText(path);
    }
}
