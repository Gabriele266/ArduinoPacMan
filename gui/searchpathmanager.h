#ifndef SEARCHPATHMANAGER_H
#define SEARCHPATHMANAGER_H

#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>

#include "packages/natural.h"

#include "settings/settings.h"

#include "newsearchpath.h"

#include "utils/utils.h"
#include "utils/macros.h"

namespace Ui {
class SearchPathManager;
}

class SearchPathManager : public QDialog
{
    Q_OBJECT

public:
    explicit SearchPathManager(QWidget *parent = nullptr);
    ~SearchPathManager();

    /**
     * @brief loadFromList Loads the base entries from a StringList.
     * @param baseEntries The base entry list
     */
    void loadFromList(QStringList* baseEntries);

    /**
     * @brief getEntriesList Returns the list with all the entries of the page
     * @return The list
     */
    QStringList getEntriesList();

    /**
      @brief Sets the settings to use for this dialog
    */
    SETTER(Settings*, settings, Settings)

private slots:
    void on_addPath_clicked();
    void on_removePath_clicked();
    void on_editCurrent_clicked();
    void on_showInBrowser_clicked();

signals:
    /**
     * @brief pathAdded Called when the user adds a new search path
     * @param newPath the path that was added
     */
    void pathAdded(QString newPath);

    /**
     * @brief pathRemoved called when a search path is removed from the list
     * @param path The path that was removed
     */
    void pathRemoved(QString path);

    /**
    * @brief Chiamato quando si modifica un percorso
    * @arg index Indice del percorso
    * @arg oldVal indica il percorso vecchio
    * @arg newVal indica il percorso nuovo
    * */
    void pathEdited(Natural index, QString oldVal, QString newVal);

private:
    Ui::SearchPathManager *ui;

    // Lista delle entries di ricerca
    QStringList entries;

    // Pointer to the settings to use
    Settings *settings = nullptr;
protected:

    /**
     * @brief updateItemsCounter Updates the counter of the libraries
     */
    void updateItemsCounter();

    /**
     * @brief updateItemsView updates the list of the items in the widget
     */
    void updateItemsView();

    /**
     * @brief addEntry adds a path to the displayed entries
     * @param path The path to add to
     */
    void addEntry(QString path);

    /**
     * @brief editItem Changes the item with the given index, applying the new name
     * @param index The index of the item to change
     * @param newVal The new value to apply
     */
    void editItem(Natural index, QString newVal);
};

#endif // SEARCHPATHMANAGER_H
