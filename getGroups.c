#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "utils.h"

char* getGroups() {
    DIR *directory;
    char* result = NULL;
    int totalSize;
    
    /*
    Pour déterminer la taille du buffer nécessaire pour stocker les noms des groupes, on doit parcourir le répertoire des groupes et additionner la taille de chaque nom de groupe.
    */

    directory = opendir("./groups/"); // On ouvre le répertoire des groupes
    if (!directory) {
        return "[ERROR] Le répertoire ./groups/ n'existe pas ou ne peut pas être ouvert."; // Si le répertoire n'existe pas, on retourne NULL
    }

    totalSize = calculateTotalSize(directory); // On calcule la taille totale des noms de groupes
    closedir(directory); // On ferme le répertoire

    result = (char*)malloc((totalSize + 1) * sizeof(char)); // On alloue un buffer de la taille nécessaire pour stocker les noms des groupes.
    if (!result) {
        return "[ERROR] L'allocation de mémoire du buffer a échoué"; // Si l'allocation a échoué, on retourne NULL
    }

    /*
    On ouvre à nouveau le répertoire des groupes pour concaténer les noms des groupes dans result.
    */

    directory = opendir("./groups/"); // On ouvre le répertoire des groupes
    if (!directory) {
        free(result); // Si le répertoire n'existe pas, on libère la mémoire allouée pour result
        return "[ERROR] Le répertoire ./groups/ n'existe pas ou ne peut pas être ouvert."; // Et on retourne NULL
    }
    
    concatenateGroupNames(directory, result); // On concatène les noms des groupes dans result
    closedir(directory); // On ferme le répertoire
    
    return result; // On retourne result
}