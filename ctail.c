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

Please see the user manual for more detailed explanation of this program's usage. 


*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>

int processChar(char *filename,int noChar);//function declaration for processChar
int processLine(char *filename,int noLine);//function declaration for processLine


int main(int argc,char *argv[])//function header for main()
{ 
	
    if (argc == 5)//if arguments 5 ie filename -L -n no_of_characters
    {
    	int noLine = atoi(argv[4]);//convert number of characters inputted by user to integer
    	if(strcmp(argv[3],"-n") == 0 && strcmp(argv[2],"-L") == 0 && noLine > 0)//Check if order and arguments correct
    	{
    		processLine(argv[1],noLine);//function call for processLine() which passes argv[1] as filename,noLine as number of lines
    	}
    	else//error
    	{
    		write(1,"Enter -L then -n enter non-negative integer for number of lines\n",64);//print error message
    		
    	}
    }
    if (argc == 4)
    {//if those conditions satisfied check if file can be read,if file can be read print last n characters given by user

        int noChar = atoi(argv[3]);//convert number of characters inputted by user to integer
        	
        if (strcmp(argv[2],"-n") == 0 && noChar > 0)//if 3 arguments are given check if second is "-n" and 3rd is positive 
        {	
			
        	processChar(argv[1],noChar);//function call for processChar() which passes argv[1] as filename,noChar as number of characters
        
        }
        else//print error
        {
            write(1,"Enter -n then enter non-negative integer for number of characters\n",67);//print error message
            exit(2);//exit with error code of 2
        
        }
    }
    //if 2 arguments are given check if 1st is "-n" and 2nd is positive integer
    if (argc == 3)
    {	if(strcmp(argv[2],"-L") == 0)//print 10 lines for file name passed by user
    	{
    		int Line = 10;
			processLine(argv[1],Line);//function call for processLine() which passes argv[1] as filename,10 as number of lines
    		
    	}
    	if(strcmp(argv[1],"-n") == 0)//check if 1st is "-n" and 2nd is positive integer
    	{	
			int noChar = atoi(argv[2]);//convert number of characters inputted by user to integer
			//printf("%d",noChar);
		    if (noChar > 0)//if number of characters inputted by user positive
		    {
		    	
		        processChar("logfile.txt",noChar);//call processChar() with "logfile.txt" as filename and noChar as number of characters
		        
		    }
		    else//print error
        	{
            	write(1,"Enter -n then enter non-negative integer for number of characters\n",67);//print error message
            	exit(2);//exit with error code of 2

        	}
		    
        }

    }
    
    if (argc == 2)
    {	//if first argument "-L"
		if(strcmp(argv[1],"-L") == 0)
		{	

			processLine("logfile.txt",10);////function call for processLine() prints lass 10 lines for logfile.txt
			
			
		}
		else
		{	//if 1 argument given check if file given can be read, if so use 200 character setting from task 1
    		processChar(argv[1],200);//function call for processChar() which passes argv[1] as filename and 200 as number of characters
		}    
    }
    if (argc == 1)
    {	//If only 1 argument given use default settings from task1
  		processChar("logfile.txt",200);
	}
}

int processChar(char *filename,int noChar)
{	//Arguments - filename:name of file from which it has to be read
	//noChar:last number of characters to be printed
	//Returns 1 if file can't be opened
	//Returns 0 at successful completion of code
	//The func
	char buffer[1024];//stores file content
    int fileid = open(filename,O_RDONLY);//Opens file logfile.txt to be read
	char openError[] = "Can't open file\n";//dtring to be printed when file isn't opened
	if (fileid < 0)//if fileid is -1,it means the file hasn't been opened
    {   
        write(STDERR_FILENO,openError,sizeof(openError)-1);//write string openError to terminal
        return 1;//exit code with return value of 1
    }
    int readBytes;//stores number of bytes read
    readBytes = read(fileid,buffer,sizeof(buffer));//reads logfile.txt into string fileContent
    if (strlen(buffer) <= noChar)//if characters in file less than or equal to characters mentioned by user
    {
    	write(1,buffer,readBytes);//write whole file into termnal
    }
    else//else print last 200 characters of file
    {
    	lseek(fileid,-noChar,SEEK_END);//place fileid at position entered by user from last
    	int Bytesread = read(fileid,buffer,sizeof(buffer));//stores number of bytes read
    	write(1,buffer,Bytesread);//writes last 200 characters in terminal
    }
    

    close(fileid);//close file
    exit(0);//exit program with error code of 0
}
int processLine(char *filename,int noLine)
{
    char buffer[1024];
    int fileid = open(filename,O_RDONLY);//Opens file logfile.txt to be read
	char openError[] = "Can't open file\n";//dtring to be printed when file isn't opened
	if (fileid < 0)//if fileid is -1,it means the file hasn't been opened
    {   
        write(STDERR_FILENO,openError,sizeof(openError)-1);//write string openError to terminal
        return 1;//exit code with return value of 1
    }
    int readBytes = read(fileid,buffer,sizeof(buffer));
    int countLine = 0;
    for (int i=0;i<=readBytes;i++)
    {
    	if(buffer[i] == '\n')
    	{
    		countLine+=1;
    	}
    }
    //countLine = countLine - 1;
    int posLine[countLine];
    int j=0;
    for (int i=0;i<=readBytes;i++)
    {
    	if(buffer[i] == '\n')
    	{	
    		posLine[j] = i;
    		j+=1;
    	}
    }
    if (countLine < noLine)
    {
    	write(1,buffer,readBytes);
    }
    else
    {
    	int pos = countLine - noLine;
    	pos = pos -1;
    	int curPos = posLine[pos];
    	lseek(fileid,curPos+1,SEEK_SET);
    	readBytes = read(fileid,buffer,sizeof(buffer));
    	write(1,buffer,readBytes);
    }
    

    close(fileid);//close file
    exit(0);

}
    
    	
    
	





