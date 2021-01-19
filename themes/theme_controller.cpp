/*
    Autore: cavallo gabriele
    Controlla che siano presenti tutti i file per i temi e ne carica uno
*/
#include <iostream>
#include <fstream>

using namespace std;

// Nome del file contenente le informazioni sul tema scuro
#define DARK_THEME_FILE "dark_theme.qrc"
// Nome del file contenente le informazioni sul tema chiaro
#define LIGHT_THEME_FILE "light_theme.qrc"
// Nome del file in cui mettere il tema da usare
#define TERMINAL_FILE "theme.qrc"
// FIle con l'output del programma
#define PROGRAM_OUT_FILE "out.str"

// Errori possibili
// Verificato quendo il file del tema richiesto non esiste
#define REQUESTED_THEME_FILE_NOT_EXISTS_ERROR -1
// Verificato quando il tema richiesto non esiste
#define REQUESTED_THEME_NOT_EXISTS_ERROR -2
// Verificato quando è impossibile aprire il file del tema
#define REQUESTED_THEME_FILE_OPEN_ERROR -3
// Verificato quando non è specificato nessun argomento di esecuzione del programma
#define NO_THEME_REQUESTED_ERROR -4
// Verificato quando sono stati specificati troppi parametri per l'esecuzione del programma
#define TOO_MANY_PARAMETERS_ERROR -5

/// Determina se il file esiste
bool fileExists(string name){
    // Tento di aprire il file
    ifstream f(name.c_str());

    return f.is_open();
}

/// Punto di entrata del programma
int main(int argc, char *argv[]){
    // Tento di aprire il file di out
    ofstream output(PROGRAM_OUT_FILE);
    if(output.is_open()){
        output << "Themes control started. " << endl;
        
        cout << "Executing themes control. " << endl;
        
        // Controllo che siano stati passati abbastanza argomenti
        if(argc == 2){
            // Prelevo il nome del tema
            string theme_name = argv[1];
            cout << "Requested theme: " << theme_name << endl;
            output << "Requested theme: " << theme_name << endl;
            cout << "Program name: " << argv[0] << endl;
            output << "Program name: " << argv[0] << endl;

            // Controllo
            if(theme_name == "dark"){
                // Controllo se esiste un file per il tema scuro
                if(fileExists(DARK_THEME_FILE)){
                    // Copio il file in un file terminale
                    // Creo il file su cui scrivere
                    ofstream file(TERMINAL_FILE);
                    // Avvio uno stream di lettura dal file di tema scuro
                    ifstream read(DARK_THEME_FILE);

                    // Tento di aprire i due file
                    if(file.is_open() && read.is_open()){
                        // Leggo tutto
                        while(!read.eof()){
                            char s[1];
                            read.read(s, 1);
                            file << s;
                        }
                        output << "Dark theme configurated" << endl;
                        output << "end0" << endl;
                        cout << endl << "Configuration for Dark Theme done. " << endl;
                        file.close();
                        read.close();
                        output.close();
                        return 0;
                    }
                    else{
                        output << endl << "err" << REQUESTED_THEME_FILE_OPEN_ERROR << endl;
                        cout << endl << "Requeste theme file unable to open. " << endl;
                        output.close();
                        return REQUESTED_THEME_FILE_OPEN_ERROR;
                    }
                }
                else{
                    output << endl << "err" << REQUESTED_THEME_FILE_NOT_EXISTS_ERROR << endl;
                    cout << endl << "Requested theme file does not exist. " << endl;
                    output.close();
                    return REQUESTED_THEME_FILE_NOT_EXISTS_ERROR;
                }
            }
            else if(theme_name == "light"){
                if(fileExists(LIGHT_THEME_FILE)){
                    // Copio il file in un file terminale
                    // Creo il file su cui scrivere
                    ofstream file(TERMINAL_FILE);
                    // Avvio uno stream di lettura dal file di tema scuro
                    ifstream read(LIGHT_THEME_FILE);

                    // Tento di aprire i due file
                    if(file.is_open() && read.is_open()){
                        // Leggo tutto
                        char s[1];
                        while(!read.eof()){
                            read.read(s, 1);
                            file << s;
                        }
                        // Chiudo i file
                        file.close();
                        read.close();
                        output << "Dark theme configurated" << endl;
                        output << "end0" << endl;
                        cout << endl << "Configuration for Light Theme done" << endl;
                        output.close();
                        return 0;
                    }
                    else{
                        cout << "Requested theme file open error" << endl;
                        output << "err" << REQUESTED_THEME_FILE_OPEN_ERROR;
                        output.close();
                        return REQUESTED_THEME_FILE_OPEN_ERROR;
                    }
                }
                else{
                    cout << "Requested theme file does not exist" << endl;
                    output << "err" << REQUESTED_THEME_NOT_EXISTS_ERROR;
                    output.close();
                    return REQUESTED_THEME_FILE_NOT_EXISTS_ERROR;
                }
                return 0;
            }
            else{
                cout << "Requested theme does not exist" << endl;
                output << "err" << REQUESTED_THEME_NOT_EXISTS_ERROR;
                output.close();
                return REQUESTED_THEME_NOT_EXISTS_ERROR;
            }
        }
        else if(argc > 2){
            cout << endl << "Error: too many parameters for this program. Only 1 is accepted: the theme name. " << endl;
            output << endl << "launcherr" << TOO_MANY_PARAMETERS_ERROR << endl;
            output.close();
            // Troppi parametri passati
            return TOO_MANY_PARAMETERS_ERROR;
        }
        else if(argc < 2){
            cout << endl << "Errore: nessun tema richiesto. " << endl;
            output << endl << "launcherr" << NO_THEME_REQUESTED_ERROR << endl;
            output.close();
            // Nessun tema richiesto
            return NO_THEME_REQUESTED_ERROR;
        }
    }
}