#ifndef GET_GROUP_H
#define GET_GROUP_H


typedef struct GroupResponse {
    char group_request[50]; // champ pour stocker la requête
    char csv[2048]; // champ pour stocker le csv reçu
} GroupResponse;

GroupResponse get_group(int sockfd, char* groups);

#endif
