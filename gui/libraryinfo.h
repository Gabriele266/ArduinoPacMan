#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

#include "packages/library.h"
#include "settings/settings.h"
#include "utils/utils.h"
#include "utils/macros.h"
#include "utils/costants.h"

namespace Ui {
class LibraryInfo;
}

/**
 * @brief The LibraryInfo class permette la visualizzazione delle informazioni di una libreria
 */
class LibraryInfo : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief LibraryInfo inizializza la finestra a partire da una libreria di cui visualizzare le informazioni
     * @param lib Libreria
     * @param parent Finestra parente da cui ereditare alcune informazioni
     * @param settings Impostazioni da ereditare
     */
    explicit LibraryInfo(Library *lib, Settings *settings = nullptr,  QWidget *parent = nullptr);
    ~LibraryInfo();

    /**
     * @brief loadView Carica le informazioni della libreria
     */
    void loadView();

    /**
     * @brief setLibrary Imposta la libreria da utilizzare
     * @param lib Puntatore alla libreria
     */
    void setLibrary(Library* lib);

    /**
     * @brief applySettings Indica alla finestra di applicare le impostazioni specifiche
     * @param settings Puntatore alle impostazioni
     */
    void applySettings(Settings *settings);


private:
    Ui::LibraryInfo *ui;
    // Libreria di cui visualizzare le informazioni
    Library *library = nullptr;
    // Impostazioni
    Settings *settings = nullptr;

protected:
    /**
     * @brief loadLibraryInfo carica le informazioni delle libreria nella finestra
     */
    void loadLibraryInfo();
};

#endif // LIBRARYINFO_H
