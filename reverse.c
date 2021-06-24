#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void usage(int err, char **para){
    if (err==1) fprintf(stderr, "usage: %s TargetFile", para[0]);
    if (err==2) fprintf(stderr, "can't not open %s", para[1]);
    exit(1);
}

int main(int argc, char **argv){
    int fd_1, fd_2;
    int readCnt;
    char Buf_1[4096], Buf_2[4096];

    if (argc!=2) usage(1, argv);
    fd_1=open(argv[1], O_RDWR);
    if (fd_1<0) usage(2, argv);
    fd_2=open(argv[1], O_RDWR);
    if (fd_2<0) usage(2, argv);
    
    lseek(fd_1, 0, SEEK_SET);
    lseek(fd_2, 0, SEEK_END);
    
    while(lseek(fd_1, 0, SEEK_CUR) < lseek(fd_2, -1, SEEK_CUR)){
        read(fd_1, Buf_1, 1);
        read(fd_2, Buf_2, 1);
        lseek(fd_1, -1, SEEK_CUR);
        lseek(fd_2, -1, SEEK_CUR);
        write(fd_1, Buf_2, 1);
        write(fd_2, Buf_1, 1);
        lseek(fd_2, -1, SEEK_CUR);
    }

    return 0;
}