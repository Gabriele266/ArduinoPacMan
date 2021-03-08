#include "librarytab.h"
#include "ui_librarytab.h"

LibraryTab::LibraryTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LibraryTab)
{
    ui->setupUi(this);
}

bool LibraryTab::load(){
    if(library != nullptr){
        if(package != nullptr){
            ui->tabTitle->setText("Informazioni libreria pacchetto " + package->getName());
            ui->libraryName->setText(library->getName());
            ui->libraryPath->setText(library->getCompletePath());

            // Check the creation date info
            QString cDate = library->getCreationDateString();
            if(cDate == "") cDate = "Nessuna informazione";
            ui->libraryCreationDate->setText(cDate);

            // Check the last modify info
            QString lDate = library->getLastModifyDateString();
            if(lDate == "") lDate = "Nessuna informazione";
            ui->libraryLastModify->setText(lDate);

            // Set the dirs flags
            ui->libraryHasDocumentation->setChecked(library->hasDocumentationDir());
            ui->libraryHasExamples->setChecked(library->hasExamples());
            ui->libraryHasKeywords->setChecked(library->hasKeywordsFile());

            // Check the description
            QString desc = library->getDescription();
            if(desc == "") desc = "Nessuna descrizione fornita. ";
            ui->libraryDescriptionBrowser->setHtml(desc);

            // Check the tags
            QStringList *tags = library->getTagsList();
            if(tags->count() > 0){
                // TODO: Implementare visualizzazione tag
            }
            else{
                ui->libraryTags->setText("Nessun tag");
            }

            return true;
        }
        else{
            return false;
        }
    }
    else{
        qInfo() << "Impossibile caricare informazioni libreria. Nessuna libreria specificata. " << endl;
        return false;
    }
}

void LibraryTab::formatTabTitle(){
    if(package != nullptr){
        if(library != nullptr){
            tabTitle = library->getName() + " - " + package->getName();
        }
        else{
            tabTitle = "No library - " + package->getName();
        }
    }
    else{
        tabTitle = "Error";
    }
}

LibraryTab::~LibraryTab()
{
    delete ui;
}
