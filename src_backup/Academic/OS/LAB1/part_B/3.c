#include<stdio.h>
#include <unistd.h>

int main()
{
    printf("current programme is executing!!\n");
    printf("process id of current programme is %d\n\n\n",getpid());
   
    execlp("man","man" ,"ls", "-l", NULL);

    printf("ending");
}

/*
    the fork() call creates a new, second process that is a duplicate of the first
    while the exec() transforms the current process into a new one the current programs code, data, and stack are entirely overwritten by the new program
    and the pid does not change and it does not return anything.
*/