#include "mainwindow.h"
#include "packages/natural.h"

#include <QApplication>
#include "file_types/group.h"
#include "file_types/key.h"
#include "file_types/settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Settings set;
    Group *group = new Group();
    group->setName("main-group");
    group->addKey(new Key("Colore", "Rosso"));
    group->addKey(new Key("Dimensione", "Enorme"));
    group->addKey(new Key("Autore", "Cavallo gabriele"));

    set.addGroup(group);



    MainWindow w;

    w.show();
    return a.exec();
}
