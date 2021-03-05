#include "fileloader.h"

FileLoader::FileLoader()
{
    file_path = "";
}

FileLoader::FileLoader(QString& file){
    file_path = file;
}

void FileLoader::run(){
    if(file_path != ""){
        // Create the file object
        QFile file(file_path);

        // Reset the buffer
        buffer = "";

        // Check existance
        if(file.exists()){
            // Try to open it
            if(file.open(QIODevice::ReadOnly)){
                // Create a text stream
                QTextStream str(&file);

                // Create a variable for the current line
                QString curLine;

                while(!str.atEnd()){
                    // Read a line
                    curLine = str.readLine();
                    buffer += curLine;
                }
                // Close the file and exit
                file.close();
                exit_state = Success;
            }
            else{
                exit_state = FileOpenError;
                error_string = file.errorString();
            }
        }
        else{
            exit_state = FileNotFound;
        }
    }
    else{
        exit_state = FileNotSpecified;
    }
}

bool FileLoader::wasSuccessful(){
    if(exit_state == Success && error_string == ""){
        return true;
    }
    return false;
}

QString FileLoader::exitStateToString(FileLoaderExit exit){
    switch(exit){
    case Success:
        return "Success";
    case FileNotFound:
        return "FileNotFound";
    case FileNotSpecified:
        return "FileNotSpecified";
    case FileOpenError:
        return "FileOpenError";
    case AccessDenied:
        return "AccessDenied";
    case NotStarted:
        return "NotStarted";
    default:
        return "Error";
    }
}
