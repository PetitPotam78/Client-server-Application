#ifndef MENU_H
#define MENU_H

/* Définition de la structure pour contenir les informations de connexion */
typedef struct {
    int port; // le port de connexion
    char hostname[256]; // l'adresse IP ou le nom du serveur
} ConnectionInfo;

/* Déclaration de la fonction menu */
ConnectionInfo menu();

#endif // MENU_H
