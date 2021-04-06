#include "libraryinfo.h"
#include "ui_libraryinfo.h"

LibraryInfo::LibraryInfo(Library *lib, Settings *settings,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibraryInfo)
{
    ui->setupUi(this);
    library = lib;
    this->settings = settings;

    // Carico le informazioni della libreria
    loadLibraryInfo();
}

void LibraryInfo::loadLibraryInfo(){
    // controllo che la libreria sia stata impostata
    if(library != nullptr){
        ui->libraryName->setText(library->getName());
        ui->libraryPath->setText(library->getCompletePath());
        ui->libraryCreationDate->setText(library->getCreationDate().toString());
        ui->libraryLastModify->setText(library->getLastModifyDateString());
        ui->libraryHasDocumentation->setText(boolToString(library->hasDocumentationDir(), false));
        ui->libraryHasExamples->setText(boolToString(library->hasExamples(), false));
        ui->libraryHasKeywords->setText(boolToString(library->hasKeywordsFile(), false));
    }
    else{
        QMessageBox::critical(this, "Errore", "Si e' cercato di visualizzare le informazioni di una libreria nulla o non esistente. ");
        qInfo() << "Si e' cercato di visualizzare le informazioni di una libreria nulla o non esistente. " << endl;
    }
}

LibraryInfo::~LibraryInfo()
{
    delete ui;
}

