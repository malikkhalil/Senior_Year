#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
int main ()
{

    int pid_A, pid_B, pid_C, pid_D, pid_E, pid_F;

    int i;
    for (i = 0; i < 3; i++){
        if (i == 0){ // A forks, creates B & C
            printf("I am process A, my PID is %d.\n",getpid());
            pid_A = getpid();
            int pid = fork(); //create B
            int pid2;
            if (pid > 0){ //still in A
                pid2 = fork(); // create C
                if (pid2 == 0){
                    pid_C = getpid();
                    printf("I am process C, my PID is %d, my PPID is %d.\n", pid_C, getppid());
                }
            }
            else if (pid == 0) // in B
            {
                pid_B = getpid();
                printf("I am process B, my PID is %d, my PPID is %d.\n", pid_B, getppid());
            }

        }
        else if (i == 1){ // B forks, creates D
            int pid = getpid();
            if (pid == pid_B){
                int pid2 = fork();
                if (pid2 == 0) // in D
                {
                    pid_D = getpid();
                    printf("I am process D, my PID is %d, my PPID is %d.\n", pid_D, getppid());
                }
            }
        }
        else if (i==2){ // C forks, creates E & F
            int pid = getpid(); //get PID of current process
            int pid2;
            if (pid == pid_C){ //we are in C
                pid = fork(); // create E 
                if (pid > 0){ //still in C
                    pid2 = fork(); // create F
                    if (pid2 == 0){
                        pid_F = getpid();
                        printf("I am process F, my PID is %d, my PPID is %d.\n", pid_F, getppid());
                    }
                }
                else if (pid == 0) // in E
                {
                    pid_E = getpid();
                    printf("I am process E, my PID is %d, my PPID is %d.\n", pid_E, getppid());
                }
            }
        }

    }   
    sleep(10);
}

