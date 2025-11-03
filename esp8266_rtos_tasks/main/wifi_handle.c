#include <wifi_handle.h>
#include <help_utils.h>
#include <esp_log.h>
#include <string.h>

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
    int32_t event_id, void* event_data);

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
    else if (WIFI_EVENT_STA_CONNECTED ==  event_id)
    {

        wifi_event_sta_connected_t* event = (wifi_event_sta_connected_t*) event_data;
        ESP_LOGI(TAG, "station %s connected "MACSTR" , channel=%d \n",
                 event->ssid, MAC2STR(event->bssid), event->channel);
    }
    else if (WIFI_EVENT_STA_DISCONNECTED ==  event_id)
    {

        wifi_event_sta_disconnected_t* event = (wifi_event_sta_disconnected_t*) event_data;
        ESP_LOGI(TAG, "station %s disconnected "MACSTR" , reason=%d \n",
                 event->ssid, MAC2STR(event->bssid), event->reason);
    }
}

void app_wifi_start(void)
{

    uint8_t mac[MAC_SIZE] = {0};
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL)); 
        wifi_config_t wifi_config = {.sta = {
            .ssid = CONFIG_ESP_WIFI_SSID,
            .password = CONFIG_ESP_WIFI_PASSWORD,
            .bssid_set = 0,
            .scan_method = WIFI_FAST_SCAN,
            .channel= 0,
            

        }};

        // memset(&wifi_config, 0, sizeof(wifi_config_t));

        // memcpy(wifi_config.ap.ssid,  EXAMPLE_ESP_WIFI_SSID, strlen(EXAMPLE_ESP_WIFI_SSID));
        // memcpy(wifi_config.ap.password,  EXAMPLE_ESP_WIFI_PASS, strlen(EXAMPLE_ESP_WIFI_PASS));
        // wifi_config.ap.ssid_len =  strlen(EXAMPLE_ESP_WIFI_SSID);
        // wifi_config.ap.authmode =  WIFI_AUTH_WPA2_PSK;


    if (strlen(CONFIG_ESP_WIFI_PASSWORD) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    printf("wificonfig %s \n",wifi_config.sta.ssid);
    printf(" %s \n",wifi_config.sta.password);
    printf("auth mode %d\n",wifi_config.sta.listen_interval);

    esp_err_t err_wifi = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);

    printf("Result %d and %x\n MAC:", err_wifi, err_wifi);
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_wifi_connect());
    
    ESP_ERROR_CHECK( esp_wifi_get_mac(ESP_IF_WIFI_STA, mac));

    show_mac(mac);
    
    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s",
             wifi_config.sta.ssid, wifi_config.sta.password);
}