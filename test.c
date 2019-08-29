#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct record
{
    int userid;
    char username[6];
};

int main(int argc, char const *argv[])
{
    int i, infile;
    struct record eachrec;
    char result[7];
    int position[] = {1, 3, 0, 2};
    int length = sizeof(position) / sizeof(int);

    /**
     * Open the file (record file) for reading
     */
    if ((infile = open("recordfile", O_RDONLY, 0400)) < 0)
    {
        perror("recordfile");
        exit(1);
    }

    for (i = 0; i < length; ++i)
    {
        /**
         * Read the record into the file
         */
        memset(result, 0, sizeof(result));
        lseek(infile, (long)position[i] * sizeof(struct record), SEEK_SET);
        read(infile, &eachrec, sizeof(struct record));
        strcat(result, eachrec.username);
        strcat(result, "\n");
        write(1, result, sizeof(result));
    }

    close(infile);
    return 0;
}