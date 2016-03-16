#include <stdio.h>
main () {
        int pid;
        int i;
        for (i=0; i<3; i++){
                if ((pid=fork()) <0 )
                {printf("Sorry...cannot fork\n"); }
                else if (pid ==0) 
                {printf("child %d\n", i);
                        fflush(stdout);
                }
                else 
                {wait();
                        printf ("parent %d\n", i);
                        fflush(stdout);
                }
        }
        exit(0);}
