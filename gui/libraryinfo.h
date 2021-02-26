#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <QDialog>

namespace Ui {
class LibraryInfo;
}

class LibraryInfo : public QDialog
{
    Q_OBJECT

public:
    explicit LibraryInfo(QWidget *parent = nullptr);
    ~LibraryInfo();

private:
    Ui::LibraryInfo *ui;
};

#endif // LIBRARYINFO_H
