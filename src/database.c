#include <stdio.h>
#include "parser.h"
#include <stdlib.h>

body_t* get_messages(){

  FILE *file = fopen("../database/database.db","rb");

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  int count = file_size/sizeof(body_t);
  body_t *messages = malloc(sizeof(body_t)*count);

  fread(messages,sizeof(body_t),count,file);
  return messages;
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


