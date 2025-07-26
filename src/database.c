#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include "formatter.h"

char* get_messages(){

  FILE *file = fopen("../database/database.db","rb");

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  int count = file_size/sizeof(body_t);
  body_t *messages = malloc(sizeof(body_t)*count);
  fread(messages,sizeof(body_t),count,file);
  
  char *response = malloc(sizeof(body_t)*(count+2)+2);

  strcpy(response, "[");  
  int total_bytes_written = 0;

  //formatting the data to json
  for (int i = count - 1; i>=0 ; i--) { 
    if(i==count-1){
    int bytes_written = sprintf(response + total_bytes_written,"[{\"username\": \"%s\", \"message\": \"%s\"},",messages[i].username,messages[i].message);
    total_bytes_written += bytes_written;
    } else if(i==0){
    int bytes_written = sprintf(response + total_bytes_written,"{\"username\": \"%s\", \"message\": \"%s\"}]",messages[i].username,messages[i].message);
    total_bytes_written += bytes_written;
    }else{
    int bytes_written = sprintf(response + total_bytes_written,"{\"username\": \"%s\", \"message\": \"%s\"},",messages[i].username,messages[i].message);
    total_bytes_written += bytes_written;
    }
      }
  //adding header and making it a proper http response
  char *res = format_json_response(response);  
  free(response); 
  free(messages);
  fclose(file);
  return res;
}

int add_message(body_t *body){

  FILE *file = fopen("../database/database.db","a+b");
  if(!file){
    perror("file");
    return -1;
  }

  fwrite(body,sizeof(body_t),1,file);
  fclose(file); 
  return 0;
}


