main ()
{

    int pid;
    int i;
    for (i=0; i<3; i++)
    {
        if ((pid=fork()) <0 ) 
        {
            printf("Sorry...cannot fork\n");
        }
        else if (pid ==0) 
        {
            printf("I'm the child. My pid is %d. My parent's pid is %d \n", getpid(), getppid());
        }
        else 
        {
            wait();
            printf("I'm the parent. My pid is %d. My child's pid is %d \n", getpid(), pid);
        }
    }
        exit(0); 
}
