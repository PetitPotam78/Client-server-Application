#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "utils.h"

char* getGroup(char* group_name) {
    FILE *file;
    char path[256];
    char* buffer = malloc(10000);
    buffer[0] = '\0';
    char ligne[2000];
    char* folder = "./groups/";
    char* filename = group_name;
    char* dotcsv = ".csv";

    remBackN(filename); // Permet de supprimer le retour à la ligne à la fin de l'en tête de la requête (GET:GROUP_NAME)

    /*
    Concatène les différentes parties du chemin du fichier à ouvrir pour avoir le chemin complet : ./groups/<group_name>.csv
    */

    strcpy(path, folder);
    strcat(path, filename);
    strcat(path, dotcsv);

    file = fopen(path, "r"); // On ouvre le fichier en lecture

    if (file == NULL) {
        printf("[ERROR] Cannot open file.\n"); // Si le fichier n'a pas pu être ouvert, on affiche un message d'erreur
        strcat(buffer, "[ERROR] Cannot open file.\n"); // On ajoute un message d'erreur dans le buffer
        fclose(file); // On ferme le fichier
    }

    while (fgets(ligne, 2000, file)) { // On lit le fichier ligne par ligne
        strcat(buffer, ligne); // On ajoute chaque ligne lue dans le buffer
    }
    
    fclose(file); // On ferme le fichier
    return buffer; // On retourne le buffer contenant le contenu du fichier
}