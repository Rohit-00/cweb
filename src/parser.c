#include "parser.h"
#include <stdio.h>
#include <string.h>

request_t parse(char *req_string){
   request_t request = {0};

    // Get the first line of the request
    char *line_end = strstr(req_string, "\r\n");
    if (!line_end) {
        fprintf(stderr, "Invalid HTTP request (missing CRLF)\n");
        return request;
    }

    // Copy just the first line
    size_t line_len = line_end - req_string;
    char line[1024] = {0};
    if (line_len >= sizeof(line)) line_len = sizeof(line) - 1;
    strncpy(line, req_string, line_len);
    line[line_len] = '\0';

    // Tokenize the request line
    char *method = strtok(line, " ");
    char *path = strtok(NULL, " ");
    char *version = strtok(NULL, " ");

    if (method) strncpy(request.method, method, sizeof(request.method) - 1);
    if (path) strncpy(request.path, path, sizeof(request.path) - 1);
    if (version) strncpy(request.version, version, sizeof(request.version) - 1);

    return request;
}

body_t parse_body(char *req_string){
    body_t msg = {0};
    char *body = strstr(req_string,"{");
    sscanf(body,
           "{\"username\":\"%82[^\"]\",\"message\":\"%255[^\"]",
           msg.username, msg.message);
    return msg;
}
