#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "utils.h"
#include "process.h"

int initialize_server(int portno) {
    int server_socket;
    struct sockaddr_in server_addr;

    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        errorMsg("Erreur lors de l'ouverture du socket", "error"); // Si l'ouverture du socket échoue, on affiche un message d'erreur
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portno);

    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        errorMsg("Erreur lors du binding", "error"); // Si le binding échoue, on affiche un message d'erreur
    }

    if (listen(server_socket, 5) < 0) {
        errorMsg("Erreur lors de la mise en écoute", "error"); // Si la mise en écoute échoue, on affiche un message d'erreur
    }
    
    return server_socket; // On retourne le descripteur du socket
}

void run_server(int server_socket) {
    struct sockaddr_in client_addr;
    unsigned int client_len;
    int client_socket;
    pid_t pid;
    
    while (1) {
        client_len = sizeof(client_addr); // On récupère la taille de l'adresse du client
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_len); // On accepte la connexion du client
        
        if (client_socket < 0) {
            errorMsg("Erreur lors de l'acceptation de la connexion", "error"); // Si la connexion échoue, on affiche un message d'erreur
        }

        errorMsg("Nouveau client connecté", "info"); // On affiche un message dans la console
        
        pid = fork();
        if (pid < 0) {
            errorMsg("Erreur lors du fork", "error"); // Si le fork échoue, on affiche un message d'erreur
        }
        
        if (pid == 0) { // Si on est dans le processus enfant
            close(server_socket); // On ferme le socket du serveur
            process(client_socket); // On traite la requête du client
            errorMsg("Client déconnecté", "info"); // On affiche un message dans la console une fois que la fonction process est terminée
            exit(0); // On quitte le processus enfant
        } else {
            close(client_socket); // On ferme le socket du client
        }
    }
}