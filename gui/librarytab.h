#ifndef LIBRARYTAB_H
#define LIBRARYTAB_H

#include <QWidget>
#include "packages/library.h"
#include "packages/package.h"

#include "utils/macros.h"
#include "gui/tab.h"

namespace Ui {
class LibraryTab;
}

class LibraryTab : public QWidget, public Tab
{
    Q_OBJECT

public:
    explicit LibraryTab(QWidget *parent = nullptr);
    ~LibraryTab();

    GETTER_SETTER(Library*, library, Library)

    GETTER_SETTER(Package*, package, Package)

    GETTER_SETTER(QString, tabTitle, TabTitle)

    /**
     * @brief load loads the informations of the library in the boxes
     */
    bool load();

    /**
     * @brief openInFiles opens the library into the file manager of the os
     */
    void openInFiles();

    /**
     * @brief openInTerminal opens the library into the terminal
     */
    void openInTerminal();

    /**
     * @brief formatTabTitle formats the tab title according to the name of the package to display and the library
     */
    void formatTabTitle();

private:
    Ui::LibraryTab *ui;

    // Library to manage
    Library *library = nullptr;
    // Pointer to the package that owns this library
    Package *package = nullptr;
    // Tab title
    QString tabTitle = "Nuovo tab";
};

#endif // LIBRARYTAB_H
