#include "filenotfoundexception.h"

FileNotFoundException::FileNotFoundException()
{
    file = "";
    operation_info = "";
}

FileNotFoundException::FileNotFoundException(QString file, QString operation_info){
    this->file = file;
    this->operation_info = operation_info;
}

FileNotFoundException::FileNotFoundException(QString file, QString operation, Natural line, QString call_file) : FileNotFoundException(file, operation){
    this->line = line;
    this->callFile = call_file;
}

QString FileNotFoundException::toString(){
    return "FileNotFoundException: The file " + file + " wasn't found. \n"
         "The operation is: " + operation_info;
}
