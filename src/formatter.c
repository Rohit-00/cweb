#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HEADER_LEN 495

char* format_response(char *body){
    size_t body_len = strlen(body);
    
    // this one is to calculate the length of the overall response 
    int response_len = snprintf(NULL, 0,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s\r\n",
        body_len, body);

    if (response_len < 0) {
        return NULL;
    }

    char* buffer = malloc(response_len+1);
    int  written = snprintf(buffer,response_len+1, 
              "HTTP/1.1 200 OK\r\n"
              "Content-Type: text/html;"
              "charset=UTF-8\r\n"
              "Content-Length: %zu\r\n"
              "Connection: close\r\n"
              "\r\n"
              "%s\r\n"
             ,body_len,body);
      return buffer;

}

char *format_json_response(const char *json_body) {
    size_t body_len = strlen(json_body);

    int res_len = snprintf(NULL, 0,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        body_len, json_body);

    if (res_len < 0) return NULL;

    char *res = malloc(res_len + 1);
    if (!res) return NULL;

    snprintf(res, res_len + 1,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        body_len, json_body);

    return res;
}

char* format_error(char *body){
  size_t body_len = strlen(body);
  char* buffer = malloc(body_len+79);

  //define error formatting logic here
}
