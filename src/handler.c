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

 if (strcmp(req.path,"/")==0 && strcmp(req.method,"GET")==0){
    FILE *file = fopen("../html/home.html","r");
    if(!file){
      perror("file");
    }

    fseek(file,0,SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *html_content = malloc(file_size + 1);
    if(!html_content){
      perror("memory allocation failed");
      fclose(file);
      return -1;
    }
    
    size_t read_size = fread(html_content, 1, file_size, file);
    fclose(file); 

    char *res = format_response(html_content);
    write(fd,res,sizeof(char)*read_size+495);
    free(res);
    free(html_content);
  }
 else if(strcmp(req.path,"/about")==0 && strcmp(req.method,"GET")==0){
    char *res = format_response("<!doctype html><html><body><p>about</p></body></html>");
    write(fd,res,sizeof(char)*4094);
    free(res);
    res = NULL;

  }
 else if(strcmp(req.path, "/whoami")==0 && strcmp(req.method,"GET")==0){
    printf("about me");
  }
 else if(strcmp(req.path,"/getdata")==0 && strcmp(req.method,"GET")==0){
    //handle request to get forum data here
  }
 else if(strcmp(req.path,"/addmsg")==0 && strcmp(req.method,"POST")==0){
    //handle post request for adding data here 
  }
 else {
    char *res = format_response("<!doctype html><html><body><p>Sorry Can't find the page you're looking for</p></body></html>");
    write(fd,res,4094);
    free(res);
    res = NULL;
  }

 return 0;
}


