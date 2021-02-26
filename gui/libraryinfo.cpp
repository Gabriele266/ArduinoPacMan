#include "libraryinfo.h"
#include "ui_libraryinfo.h"

LibraryInfo::LibraryInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibraryInfo)
{
    ui->setupUi(this);
}

LibraryInfo::~LibraryInfo()
{
    delete ui;
}
