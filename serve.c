/* serve.c */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define PORT 8181

int main()
{
  int s,c;
  socklen_t addrlen;
  struct sockaddr_in srv,cli;

  char buf[512];
  char *data;
  
  memset(&srv, 0 ,sizeof(srv));
  memset(&cli, 0, sizeof(cli));
  addrlen = 0;
  s = socket(AF_INET, SOCK_STREAM, 0); 

  if(s<0){
    printf("socket() \n");
    return -1;
  }

  srv.sin_family = AF_INET;
  srv.sin_addr.s_addr = 0;
  srv.sin_port = htons(8181);
  
  if(bind(s, (struct sockaddr*)&srv, sizeof(srv))){
    printf("bind()\n");
    close(s); return -1;
  }
  
  if(listen(s, 5)!=0){
    printf("listen()\n");
     close(s);return -1;
  }
  printf("listening on 0.0.0.0:%d\n",PORT);
  
  c = accept(s,(struct sockaddr *)&srv, &addrlen);
  
  if(c<0){
    printf("accept()\n");
   close(s);  return  -1;
  }

  
  printf("client connected\n"); 


  int n = read(c,buf,511);

  data = "httpd v1.0 \n";

  write(c,data,strlen(data));
  write(1, buf, n);
  close(c);
  close(s);
  return 0;
}
