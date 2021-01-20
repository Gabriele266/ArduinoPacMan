#ifndef SEARCHPATHMANAGER_H
#define SEARCHPATHMANAGER_H

#include <QDialog>

namespace Ui {
class SearchPathManager;
}

class SearchPathManager : public QDialog
{
    Q_OBJECT

public:
    explicit SearchPathManager(QWidget *parent = nullptr);
    ~SearchPathManager();

private:
    Ui::SearchPathManager *ui;
};

#endif // SEARCHPATHMANAGER_H
