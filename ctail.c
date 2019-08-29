#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{

    int logfile = open(argv[1], O_RDONLY); //This is included so the logfilename can be given as an argument
    int input = (int)*argv[3];
    int n;
    char Buffer[200];

    if (logfile < 0)
    {
        char *outputString = "File not found, please check the file directory!";
        write(2, outputString, strlen(outputString));
        exit(1);
    }

    n = sizeof(Buffer);
    size_t Readbytes;

    lseek(logfile, -200, SEEK_END);
    bytesRead = read(logfile, Buffer, 200);
    write(1, Buffer, Readbytes);

    close(logfile);
    return 0;
}
