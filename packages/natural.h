/* Autore: cavallo gabriele
 * Rappresenta un numero naturale e fornisce semplificazioni per il suo uso
 * */

#ifndef NATURAL_H
#define NATURAL_H

#include <QString>

/// Indica le operazioni da fare quando si vuole passare da un numero intero a un naturale
enum NaturalNumberMode{
    // Indica di usare il valroe assoluto del numero (-1 --> 1)
    UseAbsoluteValue,
    // Indica di convertire tutti i valori sotto lo zero a 0
    // -1 --> 0
    ElideUnderZero
};

/// Rappresenta un numero naturale
class Natural
{
public:
    Natural();
    Natural(int v);
    Natural(unsigned int *v);
    Natural(QString val);

    /// Imposta il valore
    void setValue(int val);
    void setValue(bool v);
    void setValue(Natural v);
    void setValue(Natural *val);

    /// Restituisce il valore per l'uso con le operazioni matematiche
    operator unsigned int();

    unsigned int getValue();

    /// Aggiunge un numero prendendo solo il valore assoluto
    void add(int val);
    void add(Natural val);
    void add(Natural *val);

    /// Toglie il valore assoluto di num al valore corrente
    void sub(int num);

    /// Imposta il valore del numero applicando una politica precisa
    void set(int num, NaturalNumberMode mode);

    /// Permette di ottenere il valore senza segno applicando una politica precisa
    static unsigned int get(int value, NaturalNumberMode mode);

    /// Effettua la differenza tra due numeri senza segno
    static unsigned int diff(unsigned int n, unsigned int n2);

    /// Restituisce una istanza della classe naturale applicando una politica precisa
    static Natural make(int value, NaturalNumberMode mode);

    unsigned int operator+(Natural left);
    unsigned int operator+(int v);

    unsigned int operator+=(Natural left);
    unsigned int operator+=(int v);
    unsigned int operator+=(Natural *val);

    unsigned int operator-(Natural val);
    unsigned int operator-(int val);
    unsigned int operator-(Natural *val);

    unsigned int operator-=(Natural n);
    unsigned int operator-=(int val);
    unsigned int operator-=(Natural *v);

    bool operator<(Natural n);
    bool operator<(int n);
    bool operator<(Natural *n);

    bool operator>(Natural n);
    bool operator>(int n);
    bool operator>(Natural *n);

    bool operator>=(Natural n);
    bool operator>=(int n);
    bool operator>=(Natural *m);

    bool operator<=(Natural n);
    bool operator<=(int n);
    bool operator<=(Natural *n);

    unsigned int operator++(int);

    void operator=(Natural n);
    void operator=(Natural *n);
    // Questo operatore causa una perdita di segno al valore (verrà applicato il valore assoluto)
    void operator=(int r);

    bool operator==(Natural n);
    /// Confronta il valore corrente con il valore assoluto del parametro
    bool operator==(int val);
    bool operator==(Natural *val);

    /// Calcola il valore assoluto del numero intero con segno e lo restituisce
    static unsigned int abs(int x);
private:
    // Valore del numero
    unsigned int val;
};

#endif // NATURAL_H
