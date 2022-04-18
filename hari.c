/*To compile: gcc shell.c  -o uab_sh
To run: ./uab_sh */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void createProces(char *inputSplit[])
{
}
void hello()
{
    printf("Hello World..!\n");
}
void fibonacci(int param)
{
    int num = param, num1 = 0, num2 = 1;
    int temp = num1 + num2;
    if (param == 0)
    {
        // printf("fib  arg :%d",param);
        printf("How many elements you want to display:");
        scanf("%d", &num);
        param = num;
    }
    printf("The first %d value: ", param);
    if (param > 0)
    {
        if (param == 1)
            printf("%d", num1);
        else
        {
            printf("%d, %d, ", num1, num2);
            for (int i = 3; i < param; ++i)
            {
                printf("%d, ", temp);
                num1 = num2;
                num2 = temp;
                temp = num1 + num2;
            }
            printf("%d", temp);
        }
    }
    printf("\n");
}
int main(int argc, char **argv)
{
    // int status;
    char input[1000], *stringSplitter, source_dir[1000];
    char *inputSplit[1000], *inputUser[1000];

    getcwd(source_dir,1000);
    if (argc != 1)
    {
        printf("Improper use, ./uab_sh <args> \n");
        return 0;
    }
    while (argv[0])
    {
        int i = 0, argCount, num = 0;
        // inputSplit[1000] = NULL;
        printf("uab_sh > ");
        fgets(input, 1000, stdin);
        char input_copy[1000];
        strcpy(input_copy,input);
         for (int j = 0; j <= 1000; j++)
                    inputSplit[j] = "\0";
        if (input[0] == '\n')
            continue;
        input[strlen(input) - 1] = '\0';
        stringSplitter = strtok(input, " ");
        while (stringSplitter != NULL)
        {
            inputSplit[i++] = stringSplitter;
            stringSplitter = strtok(NULL, " ");
        }
        for (int j = 0; j <= i; j++)
            // printf("inputSplit[%d]: %s\n", j, inputSplit[j]);
        argCount = i;
        if (strcmp(inputSplit[0], "list") == 0){
            inputSplit[0] = "ls";
        }
        if (strcmp(inputSplit[0], "quit") == 0)
        {
            return 0;
            exit(0);
        }
        char logFilePath[2000];
        strcpy(logFilePath,source_dir);
        strcat(logFilePath,"/uab_sh.log");
        int pid = fork();
        // printf("%d",pid);
        if (pid == 0)
        {
            if(strcmp(inputSplit[0],"list")==0){
            system("ls");
            }

            if (strcmp(inputSplit[0], "hello") == 0)
            {
                hello();
                for (int j = 0; j <= 1000; j++)
                    inputSplit[j] = "\0";
            }
            else if (strcmp(inputSplit[0], "fibonacci") == 0)
            {
                 for (int j = 0; j <= i; j++)
                    inputUser[j] = inputSplit[j];
                for (int j = 0; j <= 1000; j++)
                    inputSplit[j] = "\0";
                if (argCount == 2)
                {
                    num = atoi(inputUser[1]);
                    // printf("%d",num);
                    for (int j = 0; j <= i; j++)
                    {
                        inputUser[j] = "\0";
                    }
                }
                fibonacci(num);
                for (int j = 0; j <= 100; j++)
                {
                    inputSplit[j] = "\0";
                }
                exit(0);
            }
            // else if (strcmp(inputSplit[0], "quit") == 0)
            // {
            //     return 0;
            //     exit(0);
            // }
            else if (strcmp(inputSplit[0], "cd") == 0)
            {
                chdir(inputSplit[1]);
                for (int j = 0; j <= 1000; j++)
                    inputSplit[j] = "\0";
            }
            else if (strcmp(inputSplit[0], "help") == 0)
            {
                
                for (int j = 0; j <= 1000; j++)
                    inputSplit[j] = "\0";
            }
            else if(strcmp(inputSplit[0],"history") == 0)
            {
                int logFile = open(logFilePath,O_RDONLY);
                char logContents[1000];
                int n;
                while((n = read(logFile,logContents,1000)) > 0){
                    printf("%s",logContents);
                }
            }
            else
            {
                for (int j = 0; j <= 100; j++)
                    inputUser[j] = inputSplit[j];
                for (int j = 0; j <= 1000; j++)
                    inputSplit[j] = "\0";
                execvp(inputUser[0], inputUser);
                perror("exec");
                exit(-1);
            }

        }
        else
        {
            // wait(NULL);
            if (strcmp(inputSplit[0], "quit") == 0)
            {
                exit(-1);
            }
        }
        if(strcmp(inputSplit[0],"help")==0){
            printf("List of Commands are: \n");
            printf("help\n");
            printf("quit\n");
            printf("cd\n");
            printf("list\n");
            printf("fibonacci\n");
        }
        
        
        int logFile = open("uab_sh.job",O_RDONLY|O_WRONLY|O_CREAT|O_APPEND,0644);
        if (logFile < 0) 
        { 
            perror("uab_sh_error"); 
            exit(1); 
        }
        write(logFile,input_copy,strlen(input_copy));
        close(logFile);
        while (wait(NULL) != -1)
            exit(-1);
    }
    return 0;
}