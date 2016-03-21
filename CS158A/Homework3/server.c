
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 200
int main(int argc, char *argv[])
{

	if (argc < 2){
		printf("Error. Usage: ./server port");
		exit(1);
	}
   int socket_field, newsocket_field, serverlength, n;
   socklen_t clilength;
   struct sockaddr_un  cli_addr, serv_addr;
   char buf[BUFFER_SIZE];

   if ((socket_field = socket(AF_UNIX,SOCK_STREAM,0)) < 0)
    {
        printf("error creating socket. exiting now.\n");
        exit(1);
    }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sun_family = AF_UNIX;
   strcpy(serv_addr.sun_path, argv[1]);
   serverlength=strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
   if(bind(socket_field,(struct sockaddr *)&serv_addr,serverlength)<0)
    {
        printf("error binding socket. exiting now.\n");
        exit(1);
    }
   listen(socket_field,5);
   clilength = sizeof(cli_addr);
   newsocket_field = accept(socket_field,(struct sockaddr *)&cli_addr,&clilength);
   if (newsocket_field < 0) 
    {
        printf("error accepting. exiting now.\n");
        exit(1);
    }
   n=read(newsocket_field,buf,BUFFER_SIZE);
   printf("%s\n", buf);
   shutdown(newsocket_field, 2);
   close(newsocket_field);
   shutdown(socket_field, 2);
   close(socket_field);
   exit(0);
}
