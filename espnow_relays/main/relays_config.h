#ifndef RELAYS_CONFIG_H
#define RELAYS_CONFIG_H

#define ONBOARD_LED_GPIO   2  // GPIO2, czyli pin D4 na płytce
/*
gpio used by LED 2

in ESP8266 + NodeMCU it is blue led that exists on the board
*/
#define GPIO_LED  GPIO_NUM_2
/*
additional LED connected to D1 port
*/
#define GPIO_RELAY_2  GPIO_NUM_5

#define GPIO_RELAY  GPIO_NUM_4


#define GPIO_ON     (1u)

#define GPIO_OFF     (0u)

#define BUTTON_PRESSED  (0u)
#define BUTTON_RELEASED (1u)

#define RELAYS_DELAY_BETWEEN_SECOND_RELAY  (100 / portTICK_RATE_MS) 

#endif
