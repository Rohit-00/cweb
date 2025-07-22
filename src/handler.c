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

 if (strcmp(req.path,"/")==0){
    FILE *file = fopen("../html/home.html","r");
    if(!file){
      perror("file");
    }
    //getting the file size 
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
    printf("%s\n",html_content);
    fclose(file); 

    char *res = format_response(html_content);
    write(fd,res,sizeof(char)*read_size+495);
    free(res);
  }
 else if(strcmp(req.path,"/about")==0){
    printf("about page");
  }
 else if(strcmp(req.path, "/whoami")==0){
    printf("about me");
  }

 return 0;
}


