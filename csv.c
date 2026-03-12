#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isCsvFile(const char* filename) {
    /*
    Vérifie si le fichier est un fichier CSV.
    */
    int len = strlen(filename);
    char* dotcsv = ".csv";
    return (len > 4 && strcmp(filename + len - 4, dotcsv) == 0);
}

int parseCSVContent(char* received_csv, char* filename, char** data) {
    char* start = received_csv;
    char* end = strstr(received_csv, ">");
    
    if (!end) {
        return -1; // Si le caractère '>' n'est pas trouvé, on retourne 0
    }
    
    int length = end - start + 1; // On calcule la longueur de la chaîne
    strncpy(filename, start, length-1); // On copie le nom du fichier dans la variable filename
    filename[length] = '\0'; // On copie le nom du fichier dans la variable filename
    *data = received_csv + length + 1; // On copie les données dans la variable data
    
    return 0;
}

