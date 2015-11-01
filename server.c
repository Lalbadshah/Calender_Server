#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>


struct cal{
char *clname;
int dater;
int TIN;
int TOUT;
char *event;
}temp,reader;

int handler(char *funct)
{
FILE *f;

if(strcmp(funct,"add")==0)
{ 
  strcat(temp.clname,".bin");
  f=fopen(temp.clname,"ab");
  if (!f)
		{
			printf("Unable to open file!");
			return 1;
		}

  fwrite(&temp, sizeof(struct cal), 1, f);
 fclose(f);


}
if(strcmp(funct,"remove")==0)
{ printf("HELLO I AM HERE!!");
  strcat(temp.clname,".bin");
  f=fopen(temp.clname,"rb");
  if (!f)
		{
			printf("Unable to open file!");
			return 1;
		}
printf("HELLO I AM HERE!!");
  fread(&reader, sizeof(struct cal), 1, f);
 printf("READ FROM FILE!!! %s",reader.clname);
 fclose(f);


}


}






int main(int count , char *strings[])
{
char buff[100],buff1[100],buff2[100],buff4[100],*hostname,*port,*funct,*temper;
reader.clname="";
reader.dater=0;
reader.TIN=0;
reader.TOUT=0;
reader.event="";
int sock;

struct hostent *host;


hostname=strings[1];
port=strings[2];
host = gethostbyname(hostname);



socklen_t len;
int sock_desc,temp_sock;
struct sockaddr_in server,client;
sock_desc = socket(AF_INET,SOCK_STREAM,0);
if(sock_desc==-1)
{
printf("\nSocket Creation Error!\n");
exit(1);
}
server.sin_family=AF_INET;
server.sin_addr.s_addr=*(long*)(host->h_addr);
server.sin_port=htons(atoi(port));

sock=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));

if(sock==-1)
{
printf("\nBinding Error!\n");
exit(1);
}
sock=listen(sock_desc,20);
if(sock==-1)
{
printf("\nListening Error!\n");
exit(1);
}
len=sizeof(client);

temp_sock=accept(sock_desc,(struct sockaddr*)&client,&len);

if(temp_sock==-1)
{
printf("\nTemporary Socket Creation Error!\n");
exit(1);
}



{
 sock=recv(temp_sock,buff1,sizeof(buff1),0);

if(sock==-1)
{

exit(1);
}

 temp.clname=buff1;


sock=recv(temp_sock,buff2,sizeof(buff2),0);
if(sock==-1)
{
printf("\nReceiving Error!\n");
exit(1);
}
 funct=buff2;
printf("%s",funct);

sock=recv(temp_sock,buff,sizeof(buff),0);
if(sock==-1)
{
printf("\nReceiving Error!\n");
exit(1);
}

 temp.dater=atoi(buff);

sock=recv(temp_sock,buff,sizeof(buff),0);
if(sock==-1)
{
printf("\nReceiving Error!\n");
exit(1);
}
 temp.TIN=atoi(buff);

sock=recv(temp_sock,buff,sizeof(buff),0);
if(sock==-1)
{
printf("\nReceiving Error!\n");
exit(1);
}
  temp.TOUT=atoi(buff);

sock=recv(temp_sock,buff4,sizeof(buff4),0);
if(sock==-1)
{
printf("\nReceiving Error!\n");
exit(1);
}
  
temp.event=buff4;



printf("\nCLIENT DATA RECIEVED ");

//fflush(stdout);

printf("%s %s %s %d %d %d",temp.clname,funct,temp.event,temp.dater,temp.TIN,temp.TOUT);

printf("%s",funct);

strcpy(buff,"RECIEVED!");
send(temp_sock,buff,sizeof(buff),0);
handler(funct);



}
//close(temp_sock);
exit(0);
return 0;
}
