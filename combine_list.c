#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// fonction permettant de combiner le csv original avec le csv parsé avec le tag 'a' ou 'p'
char* combine_list(char* simple_list, char* full_list) {
    /* allocation dynamique pour stocker le nouveau csv */
    char* result = malloc(2048);
    result[0] = '\0'; // initialisation de la chaîne de caractères
    
    /* déclaration d'un string pour stocker l'en-tête */
    char header[256];

    /* récupération de la première ligne et ajout du champ "présence" */
    sscanf(full_list, "%[^\n]", header);
    sprintf(result, "%s;presence\n", header);
    
    /* pointeur vers le csv parsé */
    char* csv_parse = simple_list;
    /* pointeur vers le premier étudiant du csv original */
    char* original_csv = strchr(full_list, '\n') + 1;
    
    /* boucle de parcours des deux fichiers csv */
    while (*csv_parse != '\0' && *original_csv != '\0') {
        /* variables pour stocker les informations de l'étudiant parsé */
        char status;
        /* variable pour stocker une ligne du csv original */
        char line[256];
        
        /* extraction des informations de l'étudiant parsé */
        sscanf(csv_parse, "%*[^ ] %*[^ ] %c", &status);
        
        /* extraction d'une ligne du csv original */
        sscanf(original_csv, "%[^\n]", line);
        
            /* ajout de l'étudiant original avec son statut dans le nouveau csv */
            sprintf(result + strlen(result), "%s;%c\n", line, status);
        
        /* recherche du prochain retour à la ligne dans le csv parsé */
        csv_parse = strchr(csv_parse, '\n');
        /* passage au caractère suivant si un retour à la ligne a été trouvé */
        if (csv_parse != NULL) csv_parse++;
        
        /* recherche du prochain retour à la ligne dans le csv original */
        original_csv = strchr(original_csv, '\n');
        /* passage au caractère suivant si un retour à la ligne a été trouvé */
        if (original_csv != NULL) original_csv++;
    }
    
   /* retourne le csv combiné */
   return result;
}
