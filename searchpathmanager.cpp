#include "searchpathmanager.h"
#include "ui_searchpathmanager.h"

SearchPathManager::SearchPathManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchPathManager)
{
    ui->setupUi(this);
}

SearchPathManager::~SearchPathManager()
{
    delete ui;
}
