#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "csv.h"

void remBackN(char* str) {
    /*
    Renvoie la chaîne de caractères sans le caractère de fin de ligne
    */
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

int calculateTotalSize(DIR* directory) {
    /*
    Calcule la taille totale des noms de fichiers dans le répertoire.
    */

    struct dirent *dir;
    int totalSize = 0;
    
    while ((dir = readdir(directory)) != NULL) {
        if (isCsvFile(dir->d_name)) {
            totalSize += strlen(dir->d_name) + 1;
        }
    }
    
    return totalSize;
}

void concatenateGroupNames(DIR* directory, char* result) {
    /*
    Renvoie la liste des noms de fichiers dans le répertoire avec les caractères de retour à la ligne.
    */
    struct dirent *dir;
    
    result[0] = '\0';
    while ((dir = readdir(directory)) != NULL) {
        if (isCsvFile(dir->d_name)) {
            strcat(result, dir->d_name);
            strcat(result, "\n");
        }
    }
}

char* getContent(char* buffer, int n) {
    /*
    Permet de récupérer le contenu d'une requête à partir du n-ième caractère de la chaîne.
    */
    char* response = buffer+n;
    return response;
}

void errorMsg(const char *msg, char* type) {
    if (*type == "error") { 
        printf("[ERROR] %s\n", msg); // Si le type est "error", on affiche un message d'erreur sous la forme "[ERROR] UN MESSAGE"
        exit(1);
    }
    else if (type == "warning") {
        printf("[WARNING] %s\n", msg); // Si le type est "warning", on affiche un message d'avertissement sous la forme "[WARNING] UN MESSAGE"
    }
    else if (type == "info") {
        printf("[INFO] %s\n", msg); // Si le type est "info", on affiche un message d'information sous la forme "[INFO] UN MESSAGE"
    }
}
