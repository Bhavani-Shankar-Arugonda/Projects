#include<stdio.h>

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Error : invalid arguments");
        return 1;
    }

    FILE *file_ptr_input=fopen(argv[1]/*"input.c"*/,"r");
    if(file_ptr_input==NULL)
    {
        printf("Error : Input C file could not be opened");
        return 1;
    }

    FILE *file_ptr_output=fopen(argv[2]/*"output.c"*/,"w");
    if(file_ptr_output==NULL)
    {
        printf("Error : Output C file could not be created");
        fclose(file_ptr_input);
        return 1;
    }

    char a;
    while((a=fgetc(file_ptr_input))!=EOF)
    {
        char b;
        if(a=='/')
        {
            b=fgetc(file_ptr_input);
            if(b=='/')
            {
                while(b!='\n' && b!=EOF)
                {
                    b=fgetc(file_ptr_input);
                }
                if(b=='\n')
                {
                    fputc(b,file_ptr_output);
                }
            }
            else if(b=='*')
            {
                b=fgetc(file_ptr_input);
                while((b!='*' || fgetc(file_ptr_input)!='/')&& b!=EOF)
                {
                    b=fgetc(file_ptr_input);
                }
            }
        }
        else if(a=='"')
        {
            fputc('"',file_ptr_output);
            b=fgetc(file_ptr_input);
            while(b!='"')
            {
                fputc(b,file_ptr_output);
                b=fgetc(file_ptr_input);
            }
            fputc('"',file_ptr_output);
        }
        else{
            fputc(a,file_ptr_output);
        }
    }
    fclose(file_ptr_input);
    fclose(file_ptr_output);
}