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
    for(Natural x = 0; x < pathList.count(); x++){
        if(!QDir(pathList[x]).exists()){
            return false;
        }
    }
    return true;
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
