
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char *writeFunction(int input, int openfile);
char *fourArg();
char *threeArg();
char *twoArg();
char *oneArg();

int main(int argc, char const *argv[])
{
    int n;
    char buffer[200];

    n = sizeof(buffer);
    size_t bytesRead;

    char *writeFunction(int input, int openfile)
    {
        off_t size = lseek(openfile, 0, SEEK_END);
        if (size > input)
        {
            lseek(openfile, -1 * input, SEEK_END);
            //lseek(logfile,0,SEEK_SET);
            bytesRead = read(openfile, buffer, input);
            write(1, buffer, bytesRead);
            close(openfile);
        }
        else
        {
            lseek(openfile, 0, SEEK_SET);
            bytesRead = read(openfile, buffer, n);
            write(1, buffer, bytesRead);
            close(openfile);
        }
    }

    char *fourArg()
    {
        int openfile = open(argv[1], O_RDONLY);
        if (openfile < 0)
        {
            char *outputString = "File could not be found!";
            write(2, outputString, strlen(outputString));
            close(openfile);
            exit(1);
        }
        int input = atoi(argv[3]);
        if ((strcmp(argv[2], "-n") == 0))
        {
            if (atoi(argv[3]) > 0)
            {
                writeFunction(input, openfile);
            }
            else
            {
                char *outputString = "ERROR: Number is non-negative";
                write(2, outputString, strlen(outputString));
                close(openfile);
                exit(1);
            }
        }
        else
        {
            char *outputString = "ERROR: Wrong command: use -n";
            write(2, outputString, strlen(outputString));
            close(openfile);
            exit(1);
        }
    }

    char *threeArg()
    {
        int openfile = open("logfile.txt", O_RDONLY);
        int input = atoi(argv[2]);
        if ((strcmp(argv[1], "-n") == 0))
        {
            if (atoi(argv[2]) > 0)
            {
                writeFunction(input, openfile);
            }
            else
            {
                char *outputString = "ERROR: Number is non-negative";
                write(2, outputString, strlen(outputString));
                close(openfile);
                exit(1);
            }
        }
        else
        {
            char *outputString = "ERROR: Wrong command: use -n";
            write(2, outputString, strlen(outputString));
            close(openfile);
            exit(1);
        }
    }

    char *twoArg()
    {
        if (argv[1] == "logfile.txt", O_RDONLY)
        {
            int logfile = open("logfile.txt", O_RDONLY);
            writeFunction(200, logfile);
        }
        else
        {
            {
                int openfile = open(argv[1], O_RDONLY);
                writeFunction(200, openfile);
            }
        }
    }

    char *oneArg()
    {
        int logfile = open("logfile.txt", O_RDONLY);
        writeFunction(200, logfile);
    }

    if (argc == 4)
    {
        fourArg();
    }
    else if (argc == 3)
    {
        threeArg();
    }
    else if (argc == 2)
    {
        twoArg();
    }
    else if (argc == 1)
    {
        oneArg();
    }
    else
    {
        char *outputString = "Error wrong syntax: ./ctail filename.txt -n 80";
        write(2, outputString, strlen(outputString));
        exit(1);
    }

    return 0;
}