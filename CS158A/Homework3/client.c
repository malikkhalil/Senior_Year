
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE  200

int main(int argc, char *argv[])
{
   int socket_field, serverlength,n;
   struct sockaddr_un  server_address;
   char buffer[BUFFER_SIZE];
   if (argc < 3){
    printf("Error. usage: ./client port message");
    exit(1);
   }
   int i;
   int init = 0;
   for (i = 2; i < argc; i++)
   {
        if (init == 0){
            strcpy(buffer, argv[i]);
            init = 1;
        }
        else{
            strcat(buffer, " ");
            strcat(buffer, argv[i]);
        }
   }
   bzero((char *)&server_address,sizeof(server_address));
   server_address.sun_family = AF_UNIX;
   strcpy(server_address.sun_path, argv[1]);
   serverlength = strlen(server_address.sun_path) + sizeof(server_address.sun_family);
   if ((socket_field = socket(AF_UNIX, SOCK_STREAM,0)) < 0)
      {
        printf("error creating socket. exiting now.\n");
        exit(1);
      }
   if (connect(socket_field, (struct sockaddr *) &server_address, serverlength) < 0)
       {
        printf("error connecting. exiting now.\n");
        exit(1);
       }
   write(socket_field,buffer,BUFFER_SIZE);
   shutdown(socket_field, 2);
   close(socket_field);
   exit(0);
}
