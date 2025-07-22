#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* format_response(char *body){
    char* buffer = malloc(sizeof(char)*4096);
    size_t body_len = strlen(body);
    snprintf(buffer,4096, 
              "HTTP/1.1 200 OK\r\n"
              "Content-Type: text/html;"
              "charset=UTF-8\r\n"
              "Content-Length: %zu\r\n"
              "Connection:close\r\n"
              "\r\n"
             "%s\n"
             ,body_len,body);
    return buffer;
}
