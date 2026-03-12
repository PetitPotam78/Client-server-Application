#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

/* Structure pour stocker la date et l'heure */
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} CurrentTime;

CurrentTime get_current_time();

#endif

