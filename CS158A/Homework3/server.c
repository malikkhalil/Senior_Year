
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>

#DEFINE BUFFER_SIZE = 200

int main(int argc, char* argv[]){
	//Make sure port is specified.
	if (argc < 2){
		printf("Missing port argument. Usage: ./server 9000\n");
		exit(1);
	}
	int port = atoi(argv[1]);
	char buffer[BUFFER_SIZE];

	struct sockaddr_in serv_addr, cli_addr;
	socklen_t size;

	int socket = socket(AF_INET, SOCK_STREAM, 0);

	if (socket < 0){
		printf("error opening socket. will now quit.\n.");
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (bind(socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("error binding. exiting now.\n");
		exit(1);
	}
	listen(socket, 2); //wait for connection
	size = sizeof(cli_addr);
	newsock = accept(socket, (struct sockaddr *) &cli_addr, &size);
	if (newsock < 0) 
	{
		printf("error accepting. exiting now. \n");
		exit(1);
	}
	bzero(buffer, BUFFER_SIZE);
	result = read(newsock, buffer, BUFFER_SIZE-1);
	if (result < 0)
	{
		printf("error reading from the socket. exiting now.\n");
		exit(1);
	}
	printf("Message from client: %s", buffer);
	close(newsock);
	close(socket);
	exit(0);
}