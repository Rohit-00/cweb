#include "handler.h"
#include "formatter.h"
#include "parser.h"
#include "database.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <stdlib.h>

//reusable function
int serve_html(int fd,char *file_location){
    FILE *file = fopen(file_location,"r");
    if(!file){
      perror("file");
      return -1;
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
    html_content[read_size] = '\0';
    char *res = format_response(html_content);
    size_t res_len = strlen(res);
    write(fd,res,res_len);

    free(res);
    res = NULL;
    free(html_content);
    html_content = NULL;
}


int handle_connection(int fd){
  request_t req;
  body_t body;
  char buf[1024];
  
  size_t bytes_read = read(fd,buf,sizeof(buf)-1);
  if(bytes_read<0){
    perror("read");
    return -1;
  }
  buf[bytes_read] = '\0';
  char method[7];
  char path[255];
  req = parse(buf);

 //parse the request and store method and path in request_t struct
 if (strcmp(req.path,"/")==0 && strcmp(req.method,"GET")==0){
   serve_html(fd,"../html/home.html"); 
  }
 else if(strcmp(req.path,"/about")==0 && strcmp(req.method,"GET")==0){
   serve_html(fd,"../html/about.html");
  }
 else if(strcmp(req.path, "/forum")==0 && strcmp(req.method,"GET")==0){
   serve_html(fd,"../html/forum.html"); 
  }
  else if(strcmp(req.path,"/addmsg")==0 && strcmp(req.method,"POST")==0){
  body = parse_body(buf);
  int err = add_message(&body);
  }
 else {
    char *res = format_response("<!doctype html><html><body><p>Sorry Can't find the page you're looking for</p></body></html>");
    write(fd,res,4094);
    free(res);
    res = NULL;
  }

 return 0;
}


