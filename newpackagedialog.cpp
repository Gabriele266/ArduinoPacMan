#include "newpackagedialog.h"
#include "ui_newpackagedialog.h"

NewPackageDialog::NewPackageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPackageDialog)
{
    ui->setupUi(this);
    // Blocco le dimensioni della finestra
    setMaximumHeight(this->size().height());
    setMaximumWidth(this->size().width());

    setMinimumHeight(this->size().height());
    setMaximumHeight(this->size().width());

    // Popolo la lista dei caratteri non consentiti
    no_chars.append(' ');
    no_chars.append('/');
    no_chars.append('\\');
    no_chars.append('=');
    no_chars.append('(');
    no_chars.append(')');
    no_chars.append('&');
    no_chars.append('%');
    no_chars.append('$');
    no_chars.append('"');
    no_chars.append('!');
    no_chars.append('|');
    no_chars.append('?');
    no_chars.append('^');
    no_chars.append('*');
    no_chars.append('+');
    no_chars.append(']');
    no_chars.append('[');
    no_chars.append('#');
    no_chars.append('@');
    no_chars.append(':');
    no_chars.append(',');
    no_chars.append(';');
    no_chars.append('-');
    no_chars.append('<');
    no_chars.append('>');

    // Imposto il colore e lo stato di visualizzazione degli elementi per il controllo errori automatico
    // Nascondo tutto
    ui->errorLabel->setVisible(false);
    ui->correctLabel->setVisible(false);
    ui->pathIncorrect->hide();
    ui->pathCorrect->hide();

    // Imposto gli stili per le caselle
    ui->errorLabel->setStyleSheet("QLabel {"
                                    "color : red;}");
    ui->correctLabel->setStyleSheet("QLabel {"
                                    "color : green;}");

    ui->pathIncorrect->setStyleSheet("QLabel {"
                                    "color : red;}");

    ui->pathCorrect->setStyleSheet("QLabel {"
                                    "color : green;}");

    // Ottengo il pulsante per andare avanti
    continue_button = ui->buttonBox->button(QDialogButtonBox::Ok);

    // Disabilito il pulsante per andare avanti
    continue_button->setEnabled(false);

    // Avvio la autocorrezione
    on_packageName_textChanged(ui->packageName->text());
    on_packagePath_textChanged(ui->packagePath->text());
}

NewPackageDialog::~NewPackageDialog()
{
    delete ui;
}

QString NewPackageDialog::getPackageName(){
    return ui->packageName->text();
}

QString NewPackageDialog::getPackagePath(){
    return ui->packagePath->text();
}

void NewPackageDialog::on_packageName_textChanged(const QString &arg1)
{
    QString error_char = "";
    // Controllo la correttezza dei caratteri
    if(!compare(arg1, no_chars, &error_char)){
        // Controllo se il carattere non accettabile non è uno spazio
        if(error_char != " "){
            // Mostro un errore
            ui->errorLabel->setText("Carattere non accettabile: " + error_char);
        }
        else{
            // Mostro un errore
            ui->errorLabel->setText("Carattere spazio non accettabile.");
        }
        // Cambio gli stati di visualizzazione
        ui->errorLabel->setVisible(true);
        ui->correctLabel->setVisible(false);
        disableContinueWithNameError();
    }
    // Controllo la dimensione del testo
    else if(arg1.count() > 30){
        // Mostro un errore
        ui->errorLabel->setText("Nome troppo lungo. Si accettano fino a 30 caratteri.");
        ui->errorLabel->setVisible(true);
        ui->correctLabel->setVisible(false);
        disableContinueWithNameError();
    }
    else if(arg1 == ""){
        // Mostro un errore
        ui->errorLabel->setText("Nessun nome impostato. Scrivere solo lettere, \nnumeri . e _");
        ui->errorLabel->setVisible(true);
        ui->correctLabel->setVisible(false);
        // Indico che non è possibile continuare
        disableContinueWithNameError();
    }
    else{
        ui->errorLabel->setVisible(false);
        ui->correctLabel->setText("Nome accettabile");
        ui->correctLabel->setVisible(true);
        name_errors = false;
        enableContinue();
    }
}

void NewPackageDialog::disableContinueWithPathError(){
    possible = false;
    path_errors = true;
    continue_button->setEnabled(false);
}

void NewPackageDialog::disableContinueWithNameError(){
    possible = false;
    name_errors = true;
    continue_button->setEnabled(false);
}

void NewPackageDialog::enableContinue(){
    if(!name_errors && !path_errors){
        possible = true;
        continue_button->setEnabled(true);
    }
}

void NewPackageDialog::on_pushButton_clicked()
{
    // Chiedo una cartella
    QString dir = QFileDialog::getExistingDirectory(this, "Selezionare una cartella per il salvataggio del pacchetto");

    // Controllo che l'utente abbia accettato
    if(dir != ""){
        ui->packagePath->setText(dir);
    }
}

void NewPackageDialog::on_packagePath_textChanged(const QString &arg1)
{
    // Controllo che il percorso esista
    QDir dir = arg1;

    if(arg1 == ""){
        ui->pathIncorrect->setText("Nessun percorso di salvataggio impostato");
        ui->pathIncorrect->setVisible(true);
        ui->pathCorrect->setVisible(false);
        disableContinueWithPathError();
    }
    else if(!dir.exists()){
        ui->pathIncorrect->setText("Percorso non esistente");
        ui->pathIncorrect->setVisible(true);
        ui->pathCorrect->setVisible(false);
        // Disabilito la possibilità di andare avanti
        disableContinueWithPathError();
    }
    else{
        ui->pathCorrect->setText("Percorso esistente");
        ui->pathCorrect->show();
        ui->pathIncorrect->hide();
        path_errors = false;
        enableContinue();
    }
}
