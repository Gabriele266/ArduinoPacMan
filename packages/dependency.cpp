#include "dependency.h"

Dependency::Dependency()
{
    libraryName = "";
    header_name = "";
    minimal_version = Version::baseVersion();
    solved = false;
    foundLib = nullptr;
}

Dependency::Dependency(QString lib, QString header, Version minimal){
    libraryName = lib;
    header_name = header;
    minimal_version = minimal;
}

Dependency::Dependency(QString lib) : Dependency(lib, ""){

}

void Dependency::attachSource(void *source){
    source_file_caller = source;
}

Dependency Dependency::createDependency(QString lib_name, QString lib_header, Version minimal){
    Dependency newDependency;
    newDependency.setLibraryName(lib_name);
    newDependency.setHeaderName(lib_header);
    newDependency.setMinimalVersion(minimal);

    return newDependency;
}

void Dependency::closeDependency(Library *lib){
    foundLib = lib;
    solved = true;
}
