#include <stdio.h>
#include "parser.h"

int add_message(body_t *body){

  FILE *file = fopen("../database/database.db","a+b");
  if(!file){
    perror("file");
  }

  fwrite(body,sizeof(body_t),1,file);
  fclose(file); 
}
