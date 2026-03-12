#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "get_group.h"

GroupResponse get_group(int sockfd, char* groups) {
   
    char group[20]; // Stockage de l'entrée utilisateur
    GroupResponse response; // Instanciation de la struct

    /* Mise à zéro des attributs pour éviter des données indésirables */ 
    bzero(response.csv, sizeof(response.csv));
    bzero(response.group_request, sizeof(response.group_request));

    printf("\nVeuillez entrer le nom du groupe dont vous souhaitez faire l'appel :\n");
    
    /* Boucle pour vérifier la validité du groupe saisi par l'utilisateur */
    while (1) {
        char* group_list = strdup(groups); // Copie de la liste des groupes pour modification
        char* current_group = strtok(group_list, "\n");

        scanf("%s", group);
                
        while (current_group != NULL) {
            char* dot = strchr(current_group, '.');
            *dot = '\0'; // remplace le point par une fin de chaine de caractère
            
            if (strcmp(group, current_group) == 0) {
                strcpy(response.group_request, "GET:GROUP_");
                strcat(response.group_request, current_group);

                /* Envoyer la requête au serveur */
                write(sockfd, response.group_request, strlen(response.group_request));

                /* Lire la réponse du serveur */
                read(sockfd, response.csv, sizeof(response.csv) - 1);

                free(group_list); // Libérer la mémoire allouée dynamiquement
                return response; // Retourner immédiatement après avoir trouvé un groupe valide
            }
            
            current_group = strtok(NULL, "\n");
        }

        free(group_list); // Libération de la mémoire après l'échec de la recherche
        while (getchar() != '\n'); // On vide le tampon
        printf("[ERROR] Le nom du groupe est invalide. Veuillez réessayer.\n");
    }
}
