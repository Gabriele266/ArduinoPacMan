#include "newpackagedialog.h"
#include "ui_newpackagedialog.h"

NewPackageDialog::NewPackageDialog(Settings *st, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPackageDialog)
{
    ui->setupUi(this);
    settings = st;

    // Blocco le dimensioni della finestra
    setMaximumHeight(this->size().height());
    setMaximumWidth(this->size().width());

    setMinimumHeight(this->size().height());
    setMaximumHeight(this->size().width());

    // Popolo la lista dei caratteri non consentiti
    no_chars.append(' ');
    no_chars.append('\'');
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
    no_chars.append('.');
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

    ui->correctSources->setStyleSheet("QLabel {"
                                    "color : green;}");

    ui->incorrectSources->setStyleSheet("QLabel {"
                                                "color : red;}");
    // Ottengo il pulsante per andare avanti
    continue_button = ui->buttonBox->button(QDialogButtonBox::Ok);

    // Disabilito il pulsante per andare avanti
    continue_button->setEnabled(false);

    // Avvio la autocorrezione
    on_packageName_textChanged(ui->packageName->text());
    on_packagePath_textChanged(ui->packagePath->text());

    ui->correctSources->hide();
    ui->incorrectSources->show();
    // Imposto il titolo della finestra
    setWindowTitle("Creazione nuovo pacchetto");

    // Controllo se esiste già un pacchetto con il nome iniziale
    if(QDir(formatPathForOs(ui->packagePath->text(), QStringList(ui->packageName->text()) )).exists()){
        disableContinueWithNameError();
        ui->errorLabel->show();
        ui->correctLabel->hide();
        ui->errorLabel->setText("Nel percorso specificato è già presente <br>un pacchetto o una cartella con quel nome. ");
    }

    if(settings != nullptr){
        // Imposto il percorso base per i pacchetti
        ui->packagePath->setText(resolvePath(settings->getKeyValue("paths", "default-package-path")));
        ui->sourcesPath->setText(resolvePath(settings->getKeyValue("paths", "default-sources-path")));
    }
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
        // Controllo che non esista alcuna cartella con quel nome
        if(!path_errors){
            // Formatto il percorso
            QDir pt(formatPathForOs(ui->packagePath->text(), QStringList(ui->packageName->text())));
            // Controllo se esiste
            if(!pt.exists()){
                // Va tutto bene
                ui->errorLabel->setVisible(false);
                ui->correctLabel->setText("Nome accettabile");
                ui->correctLabel->setVisible(true);
                name_errors = false;
                enableContinue();
            }
            else{
                ui->errorLabel->setText("Esiste già un pacchetto o una cartella \ncon questo nome in questa cartella. ");
                ui->errorLabel->setVisible(true);
                ui->correctLabel->setVisible(false);
                name_errors = true;
                disableContinueWithNameError();
            }
        }
        else{
            ui->errorLabel->setVisible(false);
            ui->correctLabel->setText("Nome accettabile");
            ui->correctLabel->setVisible(true);
            name_errors = false;
            enableContinue();
        }
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

QString NewPackageDialog::getDescription(){
    return ui->packageDescription->toPlainText();
}

void NewPackageDialog::on_sfoglia_clicked()
{
    // Percorso da usare per il dialogo
    QString pt = ui->sourcesPath->text();
    // Directory scelta dall' utente
    QString dir;
    // Controllo se l'utente ha già impostato un percorso
    if(pt == ""){
        // Apro il browser dei file nella cartella di default per i sorgenti
        pt = settings->getKeyValue("paths", "default-sources-path");
    }

    // Apro il browser file nel percorso giusto
    dir = QFileDialog::getExistingDirectory(this, "Scegliere il percorso dei sorgenti", pt);

    if(dir != ""){
        ui->sourcesPath->setText(dir);

        // Cerco un file principale
        QStringList div = dir.split(getOSSeparator());

        // Percorso di un possibile file base
        QString base = formatPathForOs(dir, QStringList(div.last() + ".ino"));

        // Controllo se il file esiste effettivamente
        if(QFile::exists(base)){
            ui->mainFile->setText(base);
        }
    }
}

QString NewPackageDialog::getMainFilePath(){
    return ui->mainFile->text();
}

QString NewPackageDialog::getSourcesPath(){
    return ui->sourcesPath->text();
}

void NewPackageDialog::on_change_clicked()
{
    // Prendo un file
    QString file = QFileDialog::getOpenFileName(this, "Selezionare il file principale del progetto", ui->sourcesPath->text());

    if(file != ""){
        ui->mainFile->setText(file);
    }
}

void NewPackageDialog::on_buttonBox_accepted(){
}

void NewPackageDialog::on_mainFile_textChanged(const QString &arg1)
{
    // Controllo che il file esista
    if(arg1 != ""){
        // Controllo che esista
        if(QFile::exists(arg1)){
            ui->correctSources->show();
            ui->incorrectSources->hide();
            continue_button->setEnabled(true);
        }
        else{
            ui->incorrectSources->show();
            ui->correctSources->hide();
            continue_button->setEnabled(false);
        }
    }
    else{
        ui->incorrectSources->show();
        ui->correctSources->hide();
        continue_button->setEnabled(false);
    }
}
