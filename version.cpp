#include "version.h"

Version::Version()
{
    // Inizializzo tutto a 0
    major = 0;
    sub = 0;
    rev = 0;
}

Version::Version(unsigned int m, unsigned int s, unsigned int r){
    major = m;
    sub = s;
    rev = r;
}

void Version::setMajor(unsigned int v){
    major = v;
}

void Version::setSub(unsigned int v){
    sub = v;
}

void Version::setRev(unsigned int v){
    rev = v;
}

unsigned int Version::getRev(){
    return rev;
}

unsigned int Version::getMajor(){
    return major;
}

unsigned int Version::getSub(){
    return sub;
}

QString Version::toString(){
    return QString::number(major) + "." + QString::number(sub) + "." + QString::number(rev);
}

void Version::set(unsigned int m, unsigned int s, unsigned int r){
    major = m;
    sub = s;
    rev = r;
}

bool Version::parseFromString(QString version_id){
    // Controllo che la stringa non sia vuota
    if(version_id != ""){
        // Divido la stringa nei punti
        QStringList div = version_id.split('.');
        // Controllo quanti elementi sono presenti
        if(div.count() == 3){
            // Il numero è giusto
            major = div[0].toInt();
            sub = div[1].toInt();
            rev = div[2].toInt();
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

Version Version::versionFromString(QString version_id){
    // Istanza della versione
    Version ver;
    if(version_id != ""){
        // Divido in parti
        QStringList lst = version_id.split('.');

        // Controllo le dimensioni
        if(lst.count() == 3){
            ver.setMajor(lst[0].toInt());
            ver.setSub(lst[1].toInt());
            ver.setRev(lst[2].toInt());
        }
        else{
            ver.set(0, 0, 0);
        }
    }else{
        ver.set(0, 0, 0);
    }
    return ver;
}

CompareResult Version::compareVersions(Version *ver){
    // Controllo che la versione esista
    if(ver != nullptr){
        // Calcolo la somma ponderata di tutti i numeri
        int pod_sum_c = major * 3 + sub * 2 + rev * 1;
        int pod_sum_s = ver->getMajor() * 3 + ver->getSub() * 2 + ver->getRev() * 1;

        // Controllo
        if(pod_sum_c > pod_sum_s){
            return CompareResult::Major;
        }
        else if(pod_sum_c == pod_sum_s){
            return CompareResult::Equal;
        }
        else{
            return CompareResult::Minor;
        }
    }
    return CompareResult::Error;
}
