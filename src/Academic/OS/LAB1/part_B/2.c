#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t p=fork();
    
    if(p<0)
    {
        printf("Failure creatinf fork process!!");
        return 1;
    }
    else if(p==0)
    {
        printf("This is the child process!!\n");
        printf("pid of child process is %d\n",getpid());
        printf("pid of the parent of the current child process is %d\n\n",getppid());
    }
    else
    {
        printf("This is parent process!!\n");
        printf("the pid is %d\n",getpid());
        printf("the fork value returned is %d\n\n",p);
    }

    printf("implementation of fork.\n\n");
}