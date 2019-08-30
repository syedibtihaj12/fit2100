/* 
Syed Ibtihaj haque
Student ID: 27600718
Started on: 25/08/2019
Last modified: 30/08/2019

Introduction to the program:
This program reads from a file and prints out characters depending on the arguments received 
by the user. 

Default settings of this program are to print out the last 200 lines of the file it is reading 
from. 

The user can provide arguments to modify what the program can print. 

The program searches for the new line character and then 

Please see the user manual for more detailed explanation of this program's usage. 


*/

#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



int line_arg_handler(char *name_of_file, int no_line) // function definition of the line handler function which handles the line arguments passed by the user.
{
    int fileid = open(name_of_file, O_RDONLY); // opens the file.
    char buffer [1000]; // sets buffer to store characters.
    char Error[] = "The file name entered could not be opened!\n"; // Error Message.

    //the code below checks if the file has not been opened and displays the message on the screen
    if (fileid < 0) //which essentially means that the file could not be opened.
    {
        write(STDERR_FILENO, Error, sizeof(Error) - 1); //This displays the error message on the screen
        return 1; // THe program exits with a exit code 1.
    }

    int read_bytes = read(fileid, buffer, sizeof(buffer));
    int Line_count = 0;
    for(int i=0; i < read_bytes; i++)
    {
        if(buffer[i] == '\n') //Checks for the new line character and then increments the variable line_count which is counting how many lines the program has read.
        {
            Line_count+=1; // Line count is incremented.
        }
    }

    int Line_pos[Line_count];
    int temp = 0;
    for (int i =0; i<=read_bytes; i++)
    {
        if (buffer[i] == '\n')
        {
            Line_pos[temp] = i;
            temp +=1;
        }
    }

    if(Line_count < no_line)
    {
        write(1, buffer, read_bytes);
    }
    else
    {
        int position = Line_count - no_line;
        position = position -1;
        int cursor_pos = Line_pos[position];
        lseek(fileid, cursor_pos + 1, SEEK_SET);
        read_bytes = read(fileid, buffer, sizeof(buffer));
        write(1, buffer, read_bytes);

    }

    close(fileid); // Closes the file.
    exit(0); // The program exits with a error code 0.
}

int char_arg_handler(char * filename, int Char_no)// Filename is name of the file the user passes in the argument.

{
    int fileid = open(filename, O_RDONLY);
    char Error [] = "THe file cannot be opened\n";
    char buffer [1000]; //buffer to store the characters from the file.

    if(fileid < 0) // If the value of fileid is less than 0 this means file could not be opened and therefor the program would output th error message.
    {
        write(STDERR_FILENO, Error, sizeof(Error) - 1);//Error String initialised above is output to the terminal.
        return 1; //Returns with a return code 1 which means the program did not run successfully.
    }

    int read_bytes; // This is used to store the number of bytes that have been read by the program.
    read_bytes = read(fileid, buffer, sizeof(buffer)); //Reads the file mentioned by the user.

    if (strlen(buffer) <= Char_no) // If the input file has less characters as to what is given by the user as an argument, then it prints out everyting in the file.
    {
        write(1, buffer, read_bytes); // This writes the whole file content into the terminal.
    }
    else
    {
        lseek(fileid, -Char_no, SEEK_END); //Lseek function places the fileid pointer at the position mentioned by the user, starting from the end of the file.
        int bytes_read = read(fileid, buffer, sizeof(buffer)); // This stores the number of bytes 
        write(1, buffer, bytes_read); //output characters in the terminal window.
    }

    close(fileid); //The file is closed.
    exit(0); // THe program exits with the code zero.
}

int char_arg_handler( char *filename, int Char_no);
int line_arg_handler(char *filename, int Char_no);

int main(int argc, char *argv[])
{

    if (argc == 5) // If the user has given all the arguments this function will be executed. For e.g: logfile.txt -L -n 100
    {
        int line_no = atoi(argv[4]); // The statement converts number of characters of user input to integer
        if (strcmp(argv[3], "-n") == 0 && strcmp (argv[2], "-L") == 0 && line_no > 0)
        {
            line_arg_handler(argv[1], line_no);
        }
        else
        {
            write(1, "Please enter -L then -n followed by a non negative integer for number of lines\n", 64);

        }

    }


    if (argc == 4) // If the user decides to give one less argument which would be without the number of characters, then this function will be executed.
    {
        int Char_no = atoi(argv[3]); // converts the number of characters

        if (strcmp(argv[2], "-n") == 0 && Char_no > 0)// This checks if the given number is positive and the second argument is -n otherwise tells the user to enter it in correct order.
        {
            char_arg_handler(argv[1], Char_no); // Character argument handler function is called here, the file name and the number of characters are passed.
        }
        else
        {
            write(1, "Enter -n followed by a non-negative integer for number of characters\n", 67); //Error message should the user enter the arguments in incorrect order.
            exit(2); // The program exits with an error code of 2
        }
    }



    if (argc == 3) // If the user decides to give 2 arguments after the file name we have to check what they are, which is whats happening below.
    {
        if (strcmp(argv[2], "-L") == 0)// Checks if the second argument is -L the it will print out the last 10 lines of the file.
        {
            int line = 10;
            line_arg_handler(argv[1], line);// Line Argument Handler function is called here.
        }

        if (strcmp(argv[1], "-n") == 0)
        {
            int Char_no = atoi(argv[2]);

            if (Char_no > 0)
            {
                char_arg_handler("logfile.txt", Char_no);
            }
            else
            {
                write(1, "Enter -n followed by a non-negative integer for number the number of characters to be displayed\n", 67);
                exit(2);
            }
        }

    }


    if (argc == 2) //If the user decides to enter 2 arguments. This program will check if the second one is -L and will then print out the last 10 lines of the program
    {
        if (strcmp(argv[1], "-L") == 0) // THis checks if the second argument is -L
        {
            line_arg_handler("logfile.txt", 10); // Function call for the Line argument handler function
        }
        else
        {
            char_arg_handler(argv[1], 200); // function call for the character argument function because if the file contains less than 10 lines then all the content of the file will be the output in the terminal
        }

    }


    if (argc == 1) // If the user decides to enter only one argument which would be the file name, the program will just go through the file and output the last 200 characters of the file. 
    {
        char_arg_handler("logfile.txt", 200);// character function is called which outputs the last 200 characters.

    }

}

