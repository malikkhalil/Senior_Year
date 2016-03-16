#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXLINE 80
int main(int argc, char *argv[]){
	int should_run = 1;
	printf("CS149 Shell from Malik Khalil \n.");
	while(should_run){
	    char buffer[256]; //buffer for command line input
		fflush(stdout);
		fflush(stdin);
		printf("Malik-909>"); //prompt
		fflush(stdout);
		fgets(buffer, MAXLINE, stdin); //read user input
		char *output; //pointers for strtok_r
		char *saveptr;
	    
		char *args[MAXLINE/2 +1]; //space seperated input strings

		int i = 0;

		output = strtok_r(buffer, " \t\n", &saveptr);

		args[i] = output;

		i++;
		//filter input
		while (output){
			output = strtok_r(NULL, " \t\n", &saveptr);
			args[i] = output;
			i++;
			}
			args[i] = NULL;

			//if user wants to exit, exit
			if (strcmp(args[0], "exit")==0){
					should_run = 0;
					return 0;
				}
			//user entered command
			else{
				int ampersand = 0;
				//check for &
				if (strcmp(args[i-2], "&")==0){
					ampersand = 1;
					args[i-2] = NULL;

				}
				//fork
				pid_t child_pid = fork();
				//child
				if (child_pid == 0){
					int status_code = execvp(args[0], args); //execute command
					if (status_code==-1){
						//error handling
						printf("there was an error executing your command\n");
					}
					should_run = 0;
					exit(0);
				}
				//parent
				else if (child_pid > 0){
					if (ampersand == 1){
					 continue; 
					}
					else {
					 waitpid(child_pid);  //wait for child
					}
				}
				//error
				else {
					printf("\nthere was an error executing your command\n");
					continue;
				}
			}
		}
    return 0;
}
