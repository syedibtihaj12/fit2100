#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

 char *writeFn(int input, int openfile);
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

     char *writeFn(int input, int openfile)
     {
         off_t size = lseek(openfile, 0 , SEEK_END);
         bytesRead = read)openfile, buffer, input);
         write(1, buffer, bytesRead);
         close(openfile);
     }
     else
     {
        lseek(openfile, 0, SEEK_SET);
        bytesRead = read(openfile, buffer, n);
        write (1, buffer, bytesRead);
        close (openfile);
     }

     char *fourArg(){

         int openfile = open(argv[1], O_RDONLY);
         if (openfile < 0)
         {
             char * outputString = "File not found, Please make sure file is in the right directory!";
             write (2, outputString, strlen(outputString));
             close(openfile);
             exit(1);
         }

         int input = atoi(argv[3]);
         if ((strcmp(argv[2], "-n") == 0))
         {
             if (atoi(argv[3] > 0))
             {
                 writeFn(input, openfile);
             }
             else{

                 char *outputString = "The number entered is non negative, please enter a negative number";
                 write(2, outputString, strlen(outputString));
                 close (openfile;
                 exit(1);
             }
         }
         else{

             char *outputString = "The command used is not accepted, please use -n";
             write(2, outputString, strlen(outputString));
             close (openfile);
             exit(1);
         }
     }
     
     char *threeArg()
     {
         int openfile = open("logfile.txt", O_RDONLY);
         int input = atoi(argv[2]);
         if (strcmp(argv[2], "-n") == 0 )
         {
             if (atoi(argv[2] > 0))
             {
                 writeFn(input, openfile);
             }
             else
             {
                char *outputString = "The number entered is non negative";
                write(2, outputString, strlen(outputString));
                close(openfile);
                exit(1);
             }
             
         }
         else
         {
             char *outputString = "Wrong command used, please use -n";
             write(2, outputString, strlen(outputString));
             close(openfile);
             exit(1);
         }
         
     }

     char *twoArg()
     {
         if (argv[1] = "logfile.txt", O_RDONLY)
         {
             int logfile = open("logfile.txt", O_RDONLY);
             writeFn(200, logfile);
         }
         else
         {
             int openfile = open(argv[1], O_RDONLY);
             writeFn(200, openfile);
         }
         
     }
 }

 char *oneArg()
 {
     int logfile = open ("logfile", O_RDONLY);
     writeFn(200, logfile);
 }

 if (argc ==4)
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
     char *outputString = "Wrong Syntax of Arguments entered, Arguments should be entered for e.g: ./ctail logfile.txt -n 100";
     write(2, outputString, strlen(outputString));
     exit(1);
 }

 return 0;