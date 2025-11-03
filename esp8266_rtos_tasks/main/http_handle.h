#ifndef HTTP_HANDLE_H
#define HTTP_HANDLE_H
#include <esp_http_server.h>


extern esp_err_t hello_get_handler(httpd_req_t *req);

extern httpd_handle_t start_webserver(void);

extern esp_err_t echo_post_handler(httpd_req_t *req);

extern httpd_handle_t start_webserver(void);

extern esp_err_t ctrl_put_handler(httpd_req_t *req);
#endif