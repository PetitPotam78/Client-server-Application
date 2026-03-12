#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include "utils.h"
#include "getGroups.h"
#include "getGroup.h"
#include "writeGroup.h"
#include "csv.h"

#include <sys/socket.h> 

void process(int sock) { 
    int n; 
    char buffer[2048]; 
    char* response;
    char* received_csv;

    while(1) { 
        bzero(buffer,2048); 
        n = read(sock,buffer,2048);

        if (n <= 0) {
            break; // Si la lecture échoue, on sort de la boucle
        }

        if (strncmp(buffer, "GET:LIST_GROUPS", 15) == 0) {
            char* response = getGroups(); // On appelle la fonction getGroups et on l'affecte dans response
            errorMsg("Received request : GET:LIST_GROUPS", "info"); // On affiche un message dans la console
            if (response != NULL) {
                write(sock, response, strlen(response)); // On écrit la réponse dans le socket si elle n'est pas nulle
                free(response); // On libère la mémoire
            }
        }
        else if (strncmp(buffer, "GET:GROUP_", 10) == 0) {
            char* group_name = getContent(buffer, 10); // On récupère le nom du groupe
            char* response = getGroup(group_name); // On appelle la fonction getGroup et on l'affecte dans response
            errorMsg("Received request : GET:GROUP_", "info"); // On affiche un message dans la console
            if (response != NULL) {
                write(sock, response, strlen(response)); // On écrit la réponse dans le socket si elle n'est pas nulle
                free(response); // On libère la mémoire
            }
        }
        else if (strncmp(buffer, "POST:GROUP_", 11) == 0) {
            received_csv = getContent(buffer, 11); // On récupère le contenu de la requête
            char filename[100];
            char* data;
            if (parseCSVContent(received_csv, filename, &data) != 0) {
                write(sock, "[ERROR] Invalid request\n", 24); // On écrit un message d'erreur dans le socket si la requête est invalide
            } else {
                writeGroup(filename, data); // On appelle la fonction writeGroup
            }
        }
        else {
            errorMsg("Unknown command", "warning"); // On affiche un message d'erreur dans la console si la commande est inconnue
            response = "[WARNING] Unknown command\n"; // On affecte un message d'erreur dans response
            n = write(sock, response, strlen(response)); // Et on l'écrit dans le socket
        }   
    }
} 