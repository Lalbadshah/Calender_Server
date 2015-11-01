#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
int main(int count , char *strings[])
{
char buff[100],*hostname,*port,*clname,*funct,*date,*TIN,*TOUT,*event;
int sock,sock_desc;

struct hostent *host;


hostname=strings[1];
port=strings[2];
host = gethostbyname(hostname);

struct sockaddr_in client;
sock_desc = socket(AF_INET,SOCK_STREAM,0);
if(sock_desc==-1)
{
printf("\nSocket Creation Error!\n");
exit(1);
}
client.sin_family=AF_INET;
client.sin_addr.s_addr=*(long*)(host->h_addr);
client.sin_port= htons(atoi(port));

sock=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));

if(sock==-1)
{
printf("\nConnection Error!\n");
exit(1);
}

clname=strings[3];
funct=strings[4];
date=strings[5];
TIN=strings[6];
TOUT=strings[7];
event=strings[8];






{
 printf("SENDING DATA...\n");
 strcpy(buff,clname);
 sock=send(sock_desc,buff,sizeof(buff),0);
 if(sock==-1)
  {
    printf("Sending Error!");
    exit(1);
  }
  strcpy(buff,funct);
 sock=send(sock_desc,buff,sizeof(buff),0);
 if(sock==-1)
  {
    printf("Sending Error!");
    exit(1);
  }
  strcpy(buff,date);
 sock=send(sock_desc,buff,sizeof(buff),0);
 if(sock==-1)
  {
    printf("Sending Error!");
    exit(1);
  }
strcpy(buff,TIN);
 sock=send(sock_desc,buff,sizeof(buff),0);
 if(sock==-1)
  {
    printf("Sending Error!");
    exit(1);
  }
strcpy(buff,TOUT);
 sock=send(sock_desc,buff,sizeof(buff),0);
 if(sock==-1)
  {
    printf("Sending Error!");
    exit(1);
  }
strcpy(buff,event);
 sock=send(sock_desc,buff,sizeof(buff),0);
 if(sock==-1)
  {
    printf("Sending Error!");
    exit(1);
  }
recv(sock_desc,buff,sizeof(buff),0);
printf("%s\n",buff);
 
}
close(sock_desc);
exit(0);
return 0;
}
