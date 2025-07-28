#ifndef PARSER_H
#define PARSER_H

typedef struct {
  char method[10];
  char path[256];
  char version[20];
}request_t;

typedef struct {
  char username[82];
  char message[256];
} body_t;

request_t parse(char *req_string);
body_t parse_body(char *req_string);

#endif
