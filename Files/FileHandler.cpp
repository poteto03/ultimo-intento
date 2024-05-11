//
// Created by garci on 10/05/2024.
//

#include "FileHandler.h"

void FileHandler::writeToFile(char *targetFilePath, char *buffer, unsigned int bufferSize) {
    writeStream.open(targetFilePath, ios::binary);
    writeStream.write(buffer, bufferSize);
    writeStream.close();
}

char* FileHandler::readFromFile(char *targetFilePath, char* buffer, unsigned int bufferSize) {
    readStream.open(targetFilePath, ios::binary);
    //Si existe el archivo ejecuta el contenido dentro del if
    if (readStream) {
        readStream.read(buffer, bufferSize);
        readStream.close();
        return buffer;
    }
    throw 1;
}