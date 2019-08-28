#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
int main(void)
{
    char *fileContent;//string pointer which will have file content
    fileContent = (char*)malloc(1000);//malloc() dynamically allocates bytes of memory space for atmost 1000 characters.
    int fileid = open("logfile.txt",O_RDONLY);//Opens file logfile.txt to be read
	char openError[] = "Can't open file\n";//dtring to be printed when file isn't opened
	if (fileid < 0)//if fileid is -1,it means the file hasn't been opened
    {   
        write(STDERR_FILENO,openError,sizeof(openError)-1);//write string openError to terminal
        return 1;//exit code with return value of 1
    }
    int readBytes;//stores number of bytes read
    readBytes = read(fileid,fileContent,1000);//reads logfile.txt into string fileContent
    if (strlen(fileContent) <= 200)//if characters in file less than or equal to 200
    {
    	write(1,fileContent,strlen(fileContent));//write whole file into termnal
    }
    else//else print last 200 characters of file
    {
    	lseek(fileid,-200,SEEK_END);//place fileid at 200th position from last
    	int Bytesread = read(fileid,fileContent,sizeof(fileContent));//stores number of bytes read
    	write(1,fileContent,200);//writes last 200 characters in terminal
    }
    
    free(fileContent);//deallocates memory pointed to by fileContent
    close(fileid);//clse logfile.txt
    exit(0);//exit program with error code of 0
}
