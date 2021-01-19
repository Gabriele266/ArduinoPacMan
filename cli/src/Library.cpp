#include "Library.h"

Library::Library()
{
    //ctor
    name = "";
    path = "";
}

Library::Library(string name){
    this.name = name;
}

Library::Library(string name, string path) : Library(name){
    this.path = path;
}

void Library::setName(string name){
    this.name = name;
}

void Library::setDocumentationPath(string path){
    this.documentation_path = path;
}

void Library::setPath(string path){
    this.path = path;
}

void Library::setReadMeFile(string file){
    this.read_me_file = file;
}
