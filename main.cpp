#include "mainwindow.h"
#include "packages/natural.h"

#include <QApplication>
#include "file_types/group.h"
#include "file_types/key.h"
#include "file_types/settings.h"

#include "threads/settingswriter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Settings set;
    set.setFilePath("C:\\Users\\Gabri\\Documents\\codice\\impostazioni.txt");
    set.setName("Buongiorno");
    set.setDescription("Impostazioni di esempio");
    set.setCreationDate(QDate::currentDate());

    Group *group = new Group();
    group->setName("main-group");
    group->addKey(new Key("Colore", "Rosso"));
    group->addKey(new Key("Dimensione", "Enorme"));
    group->addKey(new Key("Autore", "Cavallo gabriele"));

    Group *gr = new Group();
    gr->setName("second-group");
    gr->setDescription("Seconda impostazione");
    gr->addKey(new Key("primo", "secondo", AttributeList(new Attribute("Primo", "Secondo attributo"))));
    gr->addKey(new Key("secondo", "899x800", AttributeList(
                           new Attribute(
                               "autore", "gabriele"))));
    set.addGroup(group);
    set.addGroup(gr);
    set.setKeyValue("Colore", "Verde");


    SettingsWriter *writer = new SettingsWriter();
    writer->setSettings(&set);
    writer->start();
    // Creo la finestra principale
    MainWindow w;

    w.show();
    return a.exec();
}
