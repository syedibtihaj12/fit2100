#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char *threeArg();
char *fiveArg();
char *findLineWrite(int input, int openfile);

int main(int argc, char const *argv[])
{

    int n;
    char buffer[200];

    n = sizeof(buffer);
    size_t bytesRead;

    char *fineLineWrite(int input, int openfile)
    {
        int i =0; 
        int line = 0; 
        int count =0; 
        char c;


        while (lseek(openfile, -1 * i, SEEK_END)!= -1)
        {
            read(openfile, &c, 1);
            if (c == '\n')
            {
                count ++;
            }
        i++;    
        }
        i = 0;

        int start[count];
        int end[count];
        end[0] = 1; 
        while (lseek(openfile, -1, *i, SEEK_END)!= -1)
        {
            read(openfile, &c, 1);
            if (c == '\n')
            {
                start(line) = i - 1;
                end(line + 1)= i + 1;
                line++;
            }
            i++;
        }
        start[line] = i - 1;
        line = line + 1;



        if (line > input)
        {
            input = input -1
            while (input >= 0)
            {
                lseek(openfile, -1 * start[input], SEEK_END);
                bytesRead = read(openfile, buffer, start[input] - end[input] + 2);
                write(1, buffer, bytesRead);
                input --;
            }
        }
        else
        {
            while (input >= 0)
            {
                lseek(openfile, -1 *start[input], SEEK_END);
                bytesRead = read(openfile, buffer, start[input] - end[input] + 2);
                write(1, buffer, bytesRead);
                input --;
            }
        }
        close(openfile);

    }

    char *threeArg()
    {
        int openfile = open(argv[1], O_RDONLY);
        if (openfile < 0)
        {
            char *outputString = "File not found\n";
            write(2, outputString, strlen(outputString));
            close(openfile);
            exit(1);
        }
        if ((strcmp(argv[2], "-F") == 0))
        {
            findLineWrite(10, openfile);
        }

        else
        {
            char *outputString = "THe command entered is wrong!\n";
            write(2, outputString, strlen(outputString));
            close(openfile);
            exit(1);
        }
    }

    char *fiveArg()
    {
        int openfile = open(argv[1], O_RDONLY);
        int input = atoi(argv[4]);
        if (openfile < 0)
        {
            char *outputString = "File not found\n";
            write(2, outputString, strlen(outputString));
            close(openfile);
            exit(1);
        }
        if ((strcmp(argv[2], "-F") == 0))
        {
            if ((strcmp(argv[3], "-n") == 0 ))
            {
                if (input > 0)
                {
                    findLineWrite(input, openfile);
                }
                else
                {
                    char * outputString = "Non Negative number detected, Please try again with a negative number!";
                    write(2, outputString, strlen(outputString));
                    close(openfile);
                    exit(1);
                }
            }
            else
            {
                char *outputString = "Wrong command, use -n\n";
                write(2, outputString, strlen(outputString));
                close(openfile);
                exit(1);
            }
        }
        else
        {
            char *outputString = "Wrong command, use -F\n";
            write(2, outputString, strlen(outputString));
            close(openfile);
            exit(1);
        }
    }

    if (argc == 5)
    {
        fiveArg();
    }
    else if (argc == 3)
    {
        threeArg();
    }
    else
    {
        char *outputString = "There must be either 3 or 5 arguments, Please reconsider your response.";
        write(2, outputString, strlen(outputString));
        exit(1);
    }
    return 0; 

}
