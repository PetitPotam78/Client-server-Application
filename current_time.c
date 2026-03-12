#include <stdio.h>
#include <time.h>
#include "current_time.h"

CurrentTime get_current_time() {
    time_t now; // variable de type time_t pour stocker les secondes écoulés depuis le 01/01/1970 */
    struct tm *local_time; // pointeur vers une struc tm
    CurrentTime result; // instanciation d'une struct CurrentTime
    
    /* on récupère les secondes écoulées depuis le 01/01/1970 */
    time(&now);
    
    /* on convertit en temps local en remplissant les champs de la struc_tm */
    local_time = localtime(&now);
    
    /* on récupère les informations de temps */
    result.year = local_time->tm_year + 1900; // récupération de la date
    result.month = local_time->tm_mon + 1; // récupération du mois
    result.day = local_time->tm_mday; // récupération du jour
    result.hour = local_time->tm_hour; // récupération de l'heure
    result.minute = local_time->tm_min; // récupération des minute
    result.second = local_time->tm_sec; // récupération des secondes
    
    /* on renvoie la struct contenant les informations de temps*/
    return result;
}