#include "libsearchpathlist.h"

LibSearchPathList::LibSearchPathList()
{

}

void LibSearchPathList::addPath(QString path){
    pathList.append(path);
}

QString LibSearchPathList::getPath(Natural index){
    return pathList[index];
}

Natural LibSearchPathList::getListCount(){
    return pathList.count();
}

bool LibSearchPathList::checkUp(){
    for(Natural x = 0; x < Natural::make(pathList.count(), ElideUnderZero); x++){
        if(!QDir(pathList[x]).exists()){
            return false;
        }
    }
    return true;
}

QStringList* LibSearchPathList::getEntryList(){
    return &pathList;
}

void LibSearchPathList::setSavePath(QString path){
    file_path = path;
}

QString LibSearchPathList::getSavePath(){
    return file_path;
}

void LibSearchPathList::removePath(Natural index){
    pathList.remove(index);
}

bool LibSearchPathList::editElem(Natural index, QString newVal){
    if(pathList.count() > index){
        pathList[index] = newVal;
        return true;
    }
    return false;
}

bool LibSearchPathList::removeElemByPath(QString path){
    for(Natural x = 0; x < Natural::make(pathList.count(), ElideUnderZero); x++){
        if(pathList[x] == path){
            pathList.remove(x);
            return true;
        }
    }
    return false;
}
