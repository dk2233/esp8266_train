#ifndef HELP_UTILS_H

#define HELP_UTILS_H

#include <stdio.h>
#include <stdint.h>




#define MAC_SIZE    (6u)


typedef struct 
{
    char * TaskName;
    uint32_t Period;
} TasksConfig_t;



extern const char *TAG ;


extern void show_mac(uint8_t mac[MAC_SIZE]); 

#endif