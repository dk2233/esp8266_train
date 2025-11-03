#ifndef HTTP_HANDLE_H
#define HTTP_HANDLE_H
#include <esp_http_server.h>

#define LED_HTTP_QUERY      "Led"
#define LED_HTTP_PHRASE     "<p>Led state %s <p>"

#define MAX_QUERY_SIZE      32

extern esp_err_t hello_get_handler(httpd_req_t *req);

extern httpd_handle_t start_webserver(void);

extern esp_err_t echo_post_handler(httpd_req_t *req);

extern httpd_handle_t start_webserver(void);

extern esp_err_t ctrl_put_handler(httpd_req_t *req);

extern uint8_t LedStateFromHttp;
#endif