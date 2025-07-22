#include "parser.h"
#include <stdio.h>

request_t parse(char *req_string){
    request_t request;
    sscanf(req_string,"%s %s %s", request.method,request.path,request.version);

return request;
}
