#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 8192

int main(int argc, char *argv[])
{
    int result, errno;
    int input_fd, output_fd;
    int ret_in, ret_out;

    char buffer;

    char line[BUF_SIZE];
    int j = 0;

    if (argc < 3 || argc > 3)
    {
        printf("Use command ./<executable><Number of lines><filename> ie:./mytail -n file\n");
        exit(1);
    }
    if (atoi(argv[1]) > 0)
    {

        printf("Use command ./<executable><Number of lines><filename> ie:./mytail -n file\n");
        exit(1);
    }
    input_fd = open(argv[2], O_RDONLY);
    if (input_fd == -1)
    {
        perror("open");
        return 2;
    }

    int y = 0; //Total number of lines in filee
    int z = 0; //To see in which line we are
    while ((ret_in = read(input_fd, &buffer, sizeof(char))) > 0)
    {

        if (buffer != '\n')
        {
            line[j] = buffer;
            j++;
        }
        else
        {

            memset(line, 0, sizeof(line));
            j = 0;
            y++;
        }
    }
    printf("\nTotal Number of lines:%d\n", y);
    int linesrequired = atoi(argv[1]); //Number of lines required
    if (-1 * linesrequired > y)
    {
        printf("\nError:Required lines are > than total number of lines\n");
        exit(0);
    }
    y = y + linesrequired;

    printf("Required Number of lines:%d\n\n", -1 * linesrequired);
    close(input_fd);
    input_fd = open(argv[2], O_RDONLY);

    while ((ret_out = read(input_fd, &buffer, sizeof(char))) > 0)
    {

        if (buffer != '\n')
        {
            line[j] = buffer;
            j++;
        }
        else
        {

            if (z >= y)
            {

                // printf("\nA match found in line:%d   ", x);
                printf("%s\n", line);
            }
            memset(line, 0, sizeof(line));
            j = 0;

            z++;
        }
    }
    close(input_fd);
}
