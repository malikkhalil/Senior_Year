#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAXLINE 80 /* The maximum length command */
int main(int argc, char *argv[])
{
	//char *args[MAXLINE/2 + 1]; /* command line with max 40 args */
	int should_run = 1;
	printf("CS149 Shell from Malik Khalil \n.");
	while (should_run){
		printf("Malik-909 ");
		fflush(stdout);
		char buffer[MAXLINE]; //buffer for command
		//buffer[strlen(buffer)-1] = "\0";
		//char *input = buffer; //pointer to put command in buffer
		//scanf("%[^\n]", buffer); //get user input
		fgets(&buffer, MAXLINE, stdin);
		printf("Yump");
		char *output;
		char *saveptr;
		char *args[MAXLINE/2 +1];
		int i = 0;
		output = strtok_r(buffer, " \t", &saveptr);
		args[i] = output;
		i++;
		while (output){
			output = strtok_r(NULL, " \t", &saveptr);
			args[i] = output;
			i++;
			}
		args[i] = NULL;
		
		//If user wants to exit
		printf("chemme out");
		if (strcmp(args[0], "exit")==0){
			should_run = 0;
			return 0;
		}

		//User entered a command
		else{
			int ampersand = 0;
			printf("before compare");
			if (strcmp(args[i-1], "&")==0){
				printf("comparing");
				ampersand = 1;
				args[i-1] = NULL;
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
					printf("gonna wait for child");
				 waitpid(child_pid); }
			}
			//error
			else {
				printf("\nthere was an error executing your command\n");
				continue;
			}
		}
		
    
	}
	/* After reading user input, steps are:
	* (1) fork a child process using fork()
	* (2) the child process will invoke execvp()
	* (3) if the command included &, the parent will NOT invoke wait()
	*/
    return 0;
}