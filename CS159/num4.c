main ()
{
        int pid;
        int i;
        for (i=0; i<3; i++){
                if ((pid=fork()) <0 ) 
                {printf("Sorry...cannot fork\n");
                }
                else if (pid ==0) 
                {printf("child %d\n", i);
                }
                else 
                {wait();
                        printf ("parent %d\n", i);
                }
        }
        exit(0); }
