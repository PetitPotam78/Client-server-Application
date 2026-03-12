/* simpleClientSocket.c */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include"open_socket.h"
#include"menu.h"
#include"current_groups.h"
#include"get_group.h"
#include"parse_group.h"
#include"saisie.h"
#include"combine_list.h"
#include"post_group.h"

/* 
Fichier d'entrée principal, c'est dans ce fichier que sont appelées les fonctions 
permettant le fonctionnement du client
*/

int main() {

    /* variables pour stocker les informations de connexion*/
    int portno;
    struct hostent *server;
    char tmp[2048];
    
    /* affichage du menu de connexion */
    ConnectionInfo info_con = menu();
    portno = info_con.port;
    server = gethostbyname(info_con.hostname);
    
    /* connection au serveur */
    int sock = open_socket(server,portno);
    
    /* récupération et affichage de la liste des groupes disponibles */
    char* groups = current_groups(sock);

    /* récupération du csv et de la requête envoyée */
    GroupResponse response = get_group(sock, groups);
    
    /* stockage du csv brut dans une variable temporaire */
    strcpy(tmp, response.csv);

    /* parsing du csv */
    char* parsed_csv = parse_group(response.csv);

    /* saisie des absences */
    char* updated_csv = saisie(parsed_csv);

    /* ajoute des abscences au csv de base */
    char* final_csv = combine_list(updated_csv, tmp);

    /* envoie du csv au serveur */
    post_group(sock, final_csv, response.group_request);

    /* fermeture de la connexion*/
    close(sock);

    /* libération de la mémoire */
    free(parsed_csv);
    free(updated_csv);
    free(final_csv);

    /* fin du programme */
    return 0;
}