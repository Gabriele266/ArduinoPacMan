#include "packagetab.h"
#include "ui_packagetab.h"

PackageTab::PackageTab(Package *package, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PackageTab)
{
    ui->setupUi(this);
    this->package = package;

    // Imposto le informazioni per riconoscere il tab
    setName("Package");
    setInfo("<package>");
}

void PackageTab::setTags(QString tags){
    tag = tags;
}

QString PackageTab::getTags(){
    return tag;
}

QTreeWidget* PackageTab::getFileBrowser(){
    return ui->fileBrowser;
}

QTreeWidget *PackageTab::getDependencyBrowser()
{
    return ui->dependencyBrowser;
}

Package* PackageTab::getPackage(){
    return package;
}

PackageTab::~PackageTab()
{
    delete ui;
}
