#include "handler.h"
#include "formatter.h"
#include <stdio.h>
#include <unistd.h>
#include "parser.h"
#include "string.h"
#include <stdlib.h>

int handle_connection(int fd){
  request_t req;
  char buf[465];

  if(read(fd,buf,sizeof(buf))<0){
    perror("read");
    return -1;
  }

 req = parse(buf);

 //path handling like a pro
 if (strcmp(req.path,"/")==0){
    char *res = format_response("<!DOCTYPE html><html><body><p>Hello World</p></body></html>");
    write(fd,res,sizeof(res)*4096);
    free(res);
    printf("%s",res);
  }
 else if(strcmp(req.path,"/about")==0){
    printf("about page");
  }
 else if(strcmp(req.path, "/whoami")==0){
    printf("about me");
  }

 return 0;
}


