#include "mainwindow.h"
#include "packages/natural.h"

#include <QApplication>
#include "file_types/group.h"
#include "file_types/key.h"
#include "file_types/settings.h"
#include "packages/source.h"

#include "threads/settingswriter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Creo la finestra principale
    MainWindow w;
    w.show();
    return a.exec();
}
