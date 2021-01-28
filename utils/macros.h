/*  Autore: cavallo gabriele
 *  Fornisce delle macro utile alla costruzione di classi
 * */

#ifndef MACROS_H
#define MACROS_H

/// Rappresenta un metodo getter per un determinato membro di una classe
#define GETTER(type, member, faceName) type get##faceName(){return member;}

/// Rappresenta un metodo setter per impostare un membro di una classe
#define SETTER(type, member, faceName) void set##faceName(type val){member = val;}

/// Rappresenta un metodo getter e setter per un membro di una classe
#define GETTER_SETTER(type, member, faceName) void set##faceName(type val){member = val;} type get##faceName(){return member;}

/// Si espande in una coppia di metodi getter setter con i commenti impostati
#define GETTER_SETTERC(type, member, faceName, setterComment, getterComment) \
    /** setterComment */ \
    void set##faceName(type val){member = val;} \
    /** getterComment */ \
    type get##faceName(){return member;}

/// Si espande in un metodo setter con una istruzione di set diversa da un val = membro
#define CUSTOM_SETTER(argument_type, member, faceName, custom_code) void set##faceName(argument_type mem) {member = custom_code;}

/// Fornisce un metodo per creare metodi getter con istruzioni di get diverse da return mem
#define CUSTOM_GETTER(argument_type, member, faceName, custom_code) argument_type get##faceName() {return custom_code;}

#endif // MACROS_H
