
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define IP "103.149.74.170"  /* www.google.se  */
#define PORT 8046

int main(int argc, char *argv[])
{
  int s;
  struct sockaddr_in sock;
  
  s = socket(AF_INET, SOCK_STREAM,0);
  char buf[512];
  char *data;

  data = "HEAD / HTTP/1.0\n\n";
  if(s<0){
    printf("Socket Error\n");
    return -1;
  }

  sock.sin_addr.s_addr = inet_addr(IP);
  sock.sin_port = htons(PORT); 
  sock.sin_family = AF_INET;
  
  if(connect(s,(struct sockaddr *)&sock, sizeof(struct sockaddr_in))!=0){
    printf("connect() Error\n");
    close(s);
    return -1;
  }
  
  write(s,data,strlen(data));
  read(s, buf, 511);
  close(s);

  printf("\n%s\n", buf);

  return 0;
}

