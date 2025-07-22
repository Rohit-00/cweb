#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "parser.h"
#include <stdlib.h>
#include "handler.h"

#define MAX_CLIENTS 1024

int main() {
    int listen_fd;
    fd_set readfds,writefds,master_writefds,master_readfds;
    struct sockaddr_in serverinfo = {0};
    struct sockaddr_in clientinfo = {0};
    int client_size = 0;
    int nfds = 0;
    int opt = 1;
    listen_fd = socket(AF_INET,SOCK_STREAM,0);
    if(setsockopt(listen_fd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
    perror("sockopt");
  }

    if(listen_fd == -1){
      perror("socket");
        }

    serverinfo.sin_family = AF_INET;
    serverinfo.sin_port = htons(1234);
    serverinfo.sin_addr.s_addr = 0;
    
    if(bind(listen_fd,(struct sockaddr*)&serverinfo,sizeof(serverinfo))==-1){
          perror("bind");
  }
    if(listen(listen_fd,10)==-1){
          perror("listen");
  }
    FD_ZERO(&master_readfds);
    FD_ZERO(&master_writefds);
    FD_SET(listen_fd,&master_readfds);
    nfds = listen_fd + 1;

//event loop
    while(1){
    readfds = master_readfds;
    writefds = master_writefds;

    int activity = select(FD_SETSIZE,&readfds,&writefds,NULL,NULL);
    if(activity<0) perror("select");

    for(int i = 0; i<FD_SETSIZE; i++){
      if(FD_ISSET(i,&readfds)){
        if(i==listen_fd){
          int conn_fd = accept(listen_fd,(struct sockaddr*)&clientinfo,&client_size);
          fflush(stdout);
          FD_SET(conn_fd,&master_readfds);
          FD_SET(conn_fd,&master_writefds);
          
        }else{
         FD_CLR(i,&master_readfds);
        }
      }else if(FD_ISSET(i,&writefds)){
          handle_connection(i);
          FD_CLR(i,&master_writefds);
          
        }
    }

  }
  
    close(listen_fd);
    
   return 0;
}
