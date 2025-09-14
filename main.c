#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char*argv[]){
   for(int i=1;i<argc;++i){
       int fd=open(argv[i],O_PATH);
       if(fd<0)
           continue;
       struct stat st;
       if(fstat(fd, &st))
           continue;
       printf("");
   }
   return 0;
}
