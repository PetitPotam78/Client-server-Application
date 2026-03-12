/* multipleServerSocket.c */ 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include "process.h"
#include "getGroups.h"
#include "getGroup.h"
#include "writeGroup.h"
#include "utils.h"
#include "sockets.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <port>\n", argv[0]); // Si le port n'est pas spécifié comme argument, on affiche un message d'erreur
        exit(1); // Et on quitte le programme
    }

    int server_socket = initialize_server(atoi(argv[1])); // On convertit le port en entier et on initialise le serveur
    errorMsg("Server connection initialized", "info"); // On affiche un message de confirmation

    run_server(server_socket); // On lance le serveur
    
    return 0;
}