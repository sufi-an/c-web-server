// httpd.c

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define LISTENADDR "0.0.0.0"

char *error;

int srv_init(int port){
  int s;
  struct sockaddr_in srv;

  s= socket(AF_INET, SOCK_STREAM, 0);
  
  if(s<0){
    error = "socket() error";
    return 0;
  }
  srv.sin_family = AF_INET;
  srv.sin_addr.s_addr = inet_addr(LISTENADDR);
  srv.sin_port = htons(port);

  if(bind(s,(struct sockaddr *)&srv, sizeof(srv)))
  {
    close(s);
    error = "bind() error";
    return 0;
  }

  if(listen(s,5))
  {
    close(s);
    error = "listen() error";
    return 0;
  }

  return s;

}

/* */
int cli_accept(int s){
  int c;
  socklen_t addrlen;
  struct sockaddr_in cli;
  addrlen = 0;
  memset(&cli, 0, sizeof(cli));
  c = accept(s, (struct sockaddr *)&cli, &addrlen);
  if(c<0){
    error = "accept() error";
    return 0;
  }
  return  c;
}

/**/ 
void cli_conn(int s, int c){
 return; 
}

int main(int argc, char *argv[])
{
  int s,c;
  char *port;
  if(argc<2){
    fprintf(stderr, "usage: %s <port>\n",argv[0]);
    return -1;
  }
  port = argv[1];

  s = srv_init(atoi(port));
  
  if(!s){
    fprintf(stderr, "%s\n",error);
    return -1;
  }
  
  printf("Listening on %s:%s\n",LISTENADDR, port);
  while (1) {
    c = cli_accept(s);
    if(!c){
      fprintf(stderr, "%s\n",error);
      continue;
    }

    printf("Incoming Connection\n");
    if(!fork()){
      cli_conn(s,c);
    }

    //return -1;
  }
  return 0;
}
