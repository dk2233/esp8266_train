#include "tasks.h"
#include <tcpip_adapter.h>
#include <driver/gpio.h>
#include <esp_log.h>

extern "C" {
#include <http_handle.h>
#include "ports_conf.h"
#include "help_utils.h"
#include "wifi_handle.h"
}

static const char *TAG = "MAIN";

extern "C" void app_main()
{

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    app_wifi_start();


    wifi_ap_record_t ap_record;
    esp_wifi_sta_get_ap_info(&ap_record);
    ESP_LOGI(TAG, "AP info ssid %s\n , channel %d \n",ap_record.ssid, ap_record.primary);
    show_mac(ap_record.bssid);


    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LED2, GPIO_MODE_OUTPUT);


    start_webserver();

    tasks_start();


}
