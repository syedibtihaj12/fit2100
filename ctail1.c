/*
Syed Haque 27600718
Start Date: 25/08/19
Last Modified: 30/08/2019

Description of Program

This program will check if the file name provided by the user exists or not. If the file 
exists, it will go the last 200 characters of the file using the Lseek function and 
will print that out onto the console. 

If the file has less than 200 characters, this program will output the entier file contents
and will quit normally.

I am trying to implement the line functionality as well, if it works with the allowed time, you should see the program accepting the -L argument and -n argument followed by a number to print the specified number of lines, otherwise the program will print the 10 lines by default, but if this does not work within the given time to submit the assignment, I will downgrade the assignment to do task 2 and then submit.


*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>

int processChar(char * filename, int noChar);
int processLine(char * filename, int noLine);

int main (int argc, char* argv[])
{

    if (argc == 5)
    {
        int noLine = atoi(argv[4]);
        if(strcmp(argv[3], "/n") == 0 && strcmp(argv[2], "-L") == 0 && noLine > 0)
        {
            processLine(argv[1], noLine);
        }
        else
        {
            write(1, "Wrong format detected. For Printing a number of Lines, Please enter -L -n followed by a non-negative integer for the number of Lines\n", 64);
        }
    }
    if (argc == 4)
    {

        int noChar = atoi(argv[3]); 

        if (strcmp(argv[2], "-n") == 0 && noChar > 0)
        {
            processChar(argv[1], noChar);
        }
        else
        {
            write(1, "Wrong Format detected, Please enter -n followed by a non-negative integer for the number of characters\n", 67);
            exit(2);
        }
    }

    if (argc == 3)
    {
        if (strcmp(argv[2], "-L") == 0)
        {
            int Line = 10;
            processLine(argv[1], Line);
        }
        if (strcmp(argv[1], "-n") == 0)
        {
            int noChar = atoi(argv[2]);
        
            if (noChar > 0)
            {
                processChar("logfile.txt", noChar);
            }
            else
            {
                write(1,"Wrong Format detected, Please enter -n followed by a non-negative integer for the number of characters\n", 67);
                exit(2);
            }
       }
    }

    if (argc == 2)
    {
        if (strcmp(argv[1], "-L") == 0)
        {

            processLine("logfile.txt", 10);
        }    
        else
        {
            processChar(argv[1], 200);
        }
    }
    if (argc == 1)
    {
        processChar("logfile.txt", 200);
    }
}

int processChar(char *filename, int noChar)
{
    char buffer [1024];
    int fileid = open(filename, O_RDONLY);
    char openError [] = "File cannot be opened\n";
    if (fileid < 0)
    {
        write(STDERR_FILENO, openError, sizeof(openError) - 1);
        return 1;
    }

    int readBytes;
    readBytes = read(fileid, buffer, sizeof(buffer));

    if (strlen(buffer) <= noChar)
    {
        write(1, buffer, readBytes);
    }
    else
    {
        lseek(fileid, -noChar, SEEK_END);
        int bytesRead = read(fileid, buffer, sizeof(buffer));
        write(1, buffer, bytesRead);
    }

    close(fileid);
    exit(0);
}

int processLine(char * filename, int noLine)
{
    char buffer [1];
    int fileid = open(filename, O_RDONLY);
    char openError[] = "File Cannot be opened\n";
    if (fileid < 0)
    {
        write(STDERR_FILENO, openError, sizeof(openError)- 1);
        return 1;
    }

    int countLine = 0;
    int character = 0;
    while (countLine <= noLine && buffer != "\0")
    {
        lseek(fileid, character, SEEK_END);
        int readBytes = read(fileid, buffer, 1);
        if (strcmp(buffer, "\n") == 0)
        {
            countLine++;
        }
        character ++;
    }

    write(1, buffer, character);
    
    return 0;
}