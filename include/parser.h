#ifndef PARSER_H
#define PARSER_H

typedef struct {
  char method[10];
  char path[100];
  char version[20];
}request_t;

request_t parse(char *req_string);
#endif
