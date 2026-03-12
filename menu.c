#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"

/*
fonction affichant un menu de connexion
le menu demande à l'utilisateur de saisir les informations de l'hôte distant
ces informations sont enregistrées dans un struct qui est ensuite renvoyée par la fonction
*/

ConnectionInfo menu() {
    int option; // entier pour stocker le choix de l'utilisateur
    ConnectionInfo info; // instanciation de la struct
    
    /* affichage du menu */
    printf("sélectionner, via son numéro, l'action à exécuter :\n");
    printf("1 - se connecter au serveur\n");
    printf("2 - quitter\n");
    printf("\nentrez votre choix :\n");
    
    /* boucle pour vérifier la saisie de l'utilisateur*/
    while (1) {

        /** lire le choix de l'utilisateur */
        if (scanf("%d", &option) != 1) {
            printf("[error] entrée invalide. veuillez entrer un nombre.\n");
            while (getchar() != '\n'); // vider le tampon
            continue;
        }

        /* gérer le choix de l'utilisateur */
        if (option == 1) {
            printf("\nentrez l'adresse ip ou le nom du serveur :\n");

            /* lire l'adresse ip ou le nom d'hôte */
            if (scanf("%s", info.hostname) != 1) {
                printf("[error] adresse ip ou nom invalide\n");
                while (getchar() != '\n'); // vider le tampon
                continue;
            }

            printf("entrez le port de connexion du serveur :\n");

            /* lire le port de connexion */
            if (scanf("%d", &info.port) != 1) {
                printf("[error] numéro de port invalide.\n");
                while (getchar() != '\n'); // vider le tampon
                continue;
            }

            /* retourner les informations de connexion */
            return info;

        } else if (option == 2) {
            exit(0); // quitter le programme
        } else {
            printf("[error] option invalide. veuillez réessayer.\n");
        }
    }
}
