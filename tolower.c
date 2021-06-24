#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void usage(int err, char **para){
    if (err==1) fprintf(stderr, "usage: %s TargetFile", para[0]);
    if (err==2) fprintf(stderr, "can't open %s", para[1]);
    exit(1);
}

void my_tolower(char *text){
    int len=strlen(text);
    for (int i=0; i<len; i++){
        if (text[i]>='A' && text[i]<='Z') text[i]=text[i]-'A'+'a';
    }
}

int main(int argc, char **argv){
    char Buf[4096];
    int fd_1, fd_2;
    int readCnt;

    if (argc!=2) usage(1, argv);
    fd_1=open(argv[1], O_RDONLY);
    if (fd_1<0) usage(2, argv);
    fd_2=open(argv[1], O_WRONLY);
    if (fd_2<0) usage(2, argv);

    while((readCnt=read(fd_1, Buf, 1))>0){
        my_tolower(Buf);
        write(fd_2, Buf, 1);
    }

    return 0;
}