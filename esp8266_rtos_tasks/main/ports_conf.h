/*

different functions
symbols 
related to ports usage 



*/
#ifndef PORT_CONFIG_H
#define PORT_CONFIG_H

/*
gpio used by LED 2

in ESP8266 + NodeMCU it is blue led that exists on the board
*/
#define GPIO_LED  GPIO_NUM_2
/*
additional LED connected to D1 port
*/
#define GPIO_LED2  GPIO_NUM_5

#define GPIO_ON     (1u)

#define GPIO_OFF     (0u)

#endif