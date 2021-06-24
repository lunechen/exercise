#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void usage(int err, char **para){
    if (err==1) fprintf(stderr, "usage: %s SourceFile DestinationFile\n", para[0]);
    else if (err==2) fprintf(stderr, "%s is not exist\n", para[1]);
    else if (err==3) fprintf(stderr, "%s can't not open\n", para[2]);
    exit(1);
}

int main(int argc, char **argv){
    char Buf[4096];
    int readcnt;
    int fd_1;
    int fd_2;

    if (argc!=3) usage(1, argv);
    fd_1 = open(argv[1], O_RDONLY);
    if (fd_1<0) usage(2, argv);
    fd_2 = open(argv[2], O_CREAT | O_WRONLY, 0600);
    if (fd_2<0) usage(3, argv);

    while((readcnt = read(fd_1, Buf, 1))>0){
        write(fd_2, Buf, 1);
    }

    return 0;
}