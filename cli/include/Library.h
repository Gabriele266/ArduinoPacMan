/*
* Author: Cavallo Gabriele
* Represents a library in the arduinopacman cli
*/

#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>

/// Represents a library
class Library
{
    public:
        Library();
        Library(string name);
        Library(string name, string path);

        /// Sets the name of the library
        void setName(string n);

        /// Sets the library path
        void setPath(string p);

        /// Sets the path of the documentation
        void setDocumentationPath(string p);

        /// Sets the read me file path
        void setReadMeFile(string file);

        /// Loads the library informations like keywords, directories etc
        void loadLibrary();

        /// Resturns an array containing all the file names of the library
        /// dimension in a pointer to the variable that will store the files count
        string[] getFiles(unsigned int *dimension);

        /// Returns an array containing all the sources file namese
        string[] getSourceFiles(unsigned int *count);

        /// Returns the keywords list, if exists
        string[] getKeywords(unsigned int *count);

        /// Returns the properties of the library
        string getProperties();

        /// Returns the content of the readme file, if exists
        string getReadMeInfo();

        /// Returns local variabile has_properties
        bool hasProperties();

        /// Returns true if the library has the keywords file
        bool hasKeywords();

        /// Returns true if the library has a read-me file
        bool hasReadMe();

        /// Returns true if the library info has been loaded
        bool isLoaded();

    private:
        // Name of the library
        string name;
        // Path of the library
        string path;
        // Determinates if the library has a keywords file
        bool has_keywords = false;
        // Path of the documentation
        string documentation_path;
        // Path of the read_me file
        string read_me_file;
        // Determinates that the library has some examples
        bool has_examples = false;
        // Determinates if the library has a properties file
        bool has_properties = false;

        // After loadLibrary function will be called this var will be true
        bool loaded = false;
};

#endif // LIBRARY_H
