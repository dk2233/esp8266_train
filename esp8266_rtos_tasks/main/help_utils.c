#include <help_utils.h>

void show_mac(uint8_t mac[MAC_SIZE]) 
{   
    uint8_t i = 0u;
    for(; i < MAC_SIZE-1; i++)
    {
        printf("%x::",mac[i]);
    }
    printf("%x\n",mac[i]);
}