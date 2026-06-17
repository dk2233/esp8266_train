#ifndef HELP_UTILS_H
#define HELP_UTILS_H

#include <stdint.h>
#include <stdbool.h>




#define MAC_SIZE    (6u)


typedef struct 
{
    char * TaskName;
    uint32_t Period;
} TasksConfig_t;


typedef struct 
{
    bool OutState;

} OutState_t;


extern void show_mac(uint8_t mac[MAC_SIZE]); 

#endif
