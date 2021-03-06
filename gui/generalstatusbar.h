/* Autore: cavallo gabriele
 * Rappresenta un widget per gestire la barra di stato del programma
 *
 * */

#ifndef GENERALSTATUSBAR_H
#define GENERALSTATUSBAR_H

#include <QWidget>
#include <QString>

#include "../packages/package.h"
#include "../packages/library.h"

#include "packages/natural.h"

namespace Ui {
class GeneralStatusBar;
}

class GeneralStatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralStatusBar(QWidget *parent = nullptr);
    ~GeneralStatusBar();

    /**
     * @brief setLibraryCount sets the value of the library counter
     * @param count the value to set
     */
    void setLibraryCount(Natural count);

    /**
     * @brief setCurrentPackagePath sets the path of the current package
     * @param path the path
     */
    void setCurrentPackagePath(QString path);

    /**
     * @brief setPackagesCount Sets the value of the packages counter shown
     * @param val the value to set
     */
    void setPackagesCount(Natural val);

    /**
     * @brief hidePackagesCount hides the packages count label
     */
    void hidePackagesCount();

    /**
     * @brief hideLibrariesCount Hides the libraries counter
     */
    void hideLibrariesCount();

    /**
     * @brief showLibrariesCount shows the libraries counter
     */
    void showLibrariesCount();

    /**
     * @brief showPackagesCount Shows the packages counter
     */
    void showPackagesCount();

private:
    Ui::GeneralStatusBar *ui;
};

#endif // GENERALSTATUSBAR_H
