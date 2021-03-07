#include "natural.h"

Natural::Natural()
{

}

unsigned int Natural::abs(int x){
    if(x < 0){
        return (-1) * x;
    }
    else{
        return x;
    }
}

Natural::Natural(int v){
    val = Natural::abs(v);
}

Natural::Natural(QString num){
    val = Natural::abs(num.toInt());
}

Natural::Natural(unsigned int *c){
    val = *c;
}

void Natural::setValue(int v){
    // Faccio il valore assoluto
    val = Natural::abs(v);
}

void Natural::setValue(bool v){
    val = v;
}

void Natural::setValue(Natural v){
    val = v.getValue();
}

void Natural::setValue(Natural *v){
    val = v->getValue();
}

QString Natural::toString(){
    return QString::number(val);
}

void Natural::sub(int num){
    // Prendo il valore assoluto
    auto absolute = Natural::abs(num);
    // Controllo se l'operazione ha senso
    if(absolute < val){
        // Faccio la differenza
        val -= absolute;
    }
    else{
        // Underflow
        val = 0;
    }
}

unsigned int Natural::diff(unsigned int n, unsigned int n2){
    if(n2 < n){
        return n - n2;
    }
    return 0;
}

unsigned int Natural::getValue(){
    return val;
}

Natural::operator unsigned int(){
    return val;
}

unsigned int Natural::operator+(Natural left){
    return left.getValue() + val;
}

unsigned int Natural::operator+(int v){
    return val + Natural::abs(v);
}

unsigned int Natural::operator+=(Natural left){
    val += left;
    return val;
}

unsigned int Natural::operator+=(int v){
    val += Natural::abs(v);
    return val;
}

unsigned int Natural::operator+=(Natural *v){
    val += *v;
    return val;
}

unsigned int Natural::operator++(int){
    val += 1;
    return val;
}

unsigned int Natural::operator-(Natural v){
    return Natural::diff(val, v);
}

unsigned int Natural::operator-(int v){
    return Natural::diff(val, Natural::abs(v));
}

unsigned int Natural::operator-(Natural *v){
    return Natural::diff(val, *v);
}

unsigned int Natural::operator-=(Natural n){
    sub(Natural::abs(n));
    return val;
}

unsigned int Natural::get(int value, NaturalNumberMode mode){
    switch(mode){
    case NaturalNumberMode::UseAbsoluteValue:
        return Natural::abs(value);
        break;
    case NaturalNumberMode::ElideUnderZero:
        if(value < 0){
            return 0;
        }
        else{
            return value;
        }
    }
}

Natural Natural::make(int value, NaturalNumberMode mode){
    switch(mode){
    case NaturalNumberMode::UseAbsoluteValue:
        return Natural::abs(value);
        break;
    case NaturalNumberMode::ElideUnderZero:
        if(value < 0){
            return 0;
        }
        else{
            return value;
        }
    }
}

bool Natural::operator<(Natural n){
    if(val < n.getValue()){
        return true;
    }
    return false;
}

bool Natural::operator<(int n){
    return val < (Natural::abs(n));
}

bool Natural::operator>(int n){
    return val > (Natural::abs(n));
}

bool Natural::operator>(Natural n){
    return val > n.getValue();
}

void Natural::set(int num, NaturalNumberMode mode){
    val = Natural::get(num, mode);
}

unsigned int Natural::operator-=(int v){
    sub(Natural::abs(v));
    return val;
}

unsigned int Natural::operator-=(Natural *v){
    sub(*v);
    return val;
}

void Natural::operator=(Natural n){
    val = n;
}

void Natural::operator=(Natural *n){
    val = *n;
}

bool Natural::operator<=(Natural n){
    if(val <= n.getValue()){
        return true;
    }
    return false;
}

bool Natural::operator<=(int n){
    if(val <= Natural::make(n, ElideUnderZero)){
        return true;
    }
    return false;
}

// Questo operatore causa una perdita di segno al valore (verrà applicato il valore assoluto)
void Natural::operator=(int r){
    val = Natural::abs(r);
}
