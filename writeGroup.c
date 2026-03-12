#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "utils.h"

int writeGroup(char* group_name, char* content) {
    FILE *file;
    char path[256];
    char* folder = "./appels/";
    char* filename = group_name;
    char* dotcsv = ".csv";

    remBackN(filename); // Permet de supprimer le retour à la ligne à la fin de l'en tête de la requête (POST:GROUP_NAME_DATE>\nCONTENT)

    strcpy(path, folder);
    strcat(path, filename);
    strcat(path, dotcsv);

    file = fopen(path, "w"); // On ouvre le fichier en écriture

    if (file == NULL) { 
        printf("[ERROR] Cannot open file.\n"); // Si le fichier n'a pas pu être ouvert, on affiche un message d'erreur
        fclose(file); // On ferme le fichier
        return -1; // On retourne -1 pour indiquer une erreur
    }

    fprintf(file, content); // On écrit le contenu dans le fichier
    fclose(file); // On ferme le fichier
    return 0;
}