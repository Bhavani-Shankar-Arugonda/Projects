#include<stdio.h>

int main()
{
    char a[10],*x,*y;
    x[100]=1;
    printf("%d\n", &a[10]);
    printf("%p\n",x);
    printf("%p\n",a);
    

    x=a;printf("%p\n",x);//output-0x7fff74b7e8be
    a[0]=y[0];printf("%p\n",a);

    //x=&a;printf("%p\n",a);

    x=a+2;printf("%p\n",x);

    //x=*(a+2);printf("%p\n",x);
}