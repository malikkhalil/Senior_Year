#include <stdio.h>
int main (void)
{
        printf("Line 1 ..\n");
        fflush(stdout);
        write(1,"Line 2 ",7);
}
