#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"current_groups.h"


char* current_groups(int sockfd) {

    int option; // entier pour stocker le choix de l'utiisateur
    char* get = malloc(256); // chaîne de caractère pour stocker la requête
    bzero(get, 256); // initialisation du tableau à 0

    /* affichage du menu */
    printf("\nQue souhaitez-vous faire à présent :\n");
    printf("1 - Afficher la liste des groupes\n");
    printf("2 - Quittez le client\n\n");
    printf("Entrez votre choix :\n");
    
    /* boucle pour vérifier le choix de l'utilisateur*/
    while (1) {
        /* Lire le choix de l'utilisateur*/
        scanf("%d", &option);
        
        /* si l'utilisateur saisie 1*/
        if (option == 1) {
            strcpy(get, "GET:LIST_GROUPS"); // copie la requête dans get[] 
            break; // quitter la boucle
        } else if (option == 2) { // sinon
            exit(0); // quitter le programme
        } else {
            while (getchar() != '\n'); // vider le tampon
            printf("[ERROR]Option invalide, veuillez entrer un numéro valide.\n");
        }
    }            
    
    /* envoie de la requête get au serveur */
    write(sockfd, get, strlen(get));
    
    /* lire la liste des groupes envoyés par le serveur */
    bzero(get, 256);
    read(sockfd, get, 255);        
    printf("\nVoici la liste des groupes :\n%s\n", get);

    /* on renvoie la liste des groupes */
    return get;
}