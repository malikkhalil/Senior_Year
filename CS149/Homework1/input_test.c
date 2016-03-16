#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define MAXLINE 80
int main(int argc, char *argv[]){
	int should_run = 1;
	printf("CS149 Shell from Malik Khalil \n.");
	while(should_run){
	    char buffer[256];
		fflush(stdout);
		fflush(stdin);
		printf("Malik-909>");
		fgets(buffer, MAXLINE, stdin);
		char *output;
		char *saveptr;
	    
		char *args[MAXLINE/2 +1];

		int i = 0;

		output = strtok_r(buffer, " \t\n", &saveptr);

		args[i] = output;

		i++;
		while (output){
		//printf("%s \n", output);
			output = strtok_r(NULL, " \t\n", &saveptr);
			args[i] = output;
			i++;
			}
			args[i] = NULL;
			if (strcmp(args[0], "exit")==0){
					should_run = 0;
					return 0;
				}
			else{
				int ampersand = 0;
				if (strcmp(args[i-2], "&")==0){
					ampersand = 1;
					args[i-2] = NULL;

				}
				pid_t child_pid = fork();
				//child
				if (child_pid == 0){
					int status_code = execvp(args[0], args);
					if (status_code==-1){
						printf("\nthere was an error executing your command\n");
						continue;
					}
				}
				//parent
				else if (child_pid > 0){
					if (ampersand == 1){
					 continue; 
					}
					else {
					 waitpid(child_pid); 
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
