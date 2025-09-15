#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

static void print_info(struct stat st,const char *name){
    struct tm tm=*localtime(&st.st_mtime);
    char * type[7]={//man 7 inode
        "FIFO            ","character device",
        "directory       ","block device    ",
        "regular file    ","symbolic link   ",
        "socket          "
    };
    char perm[12]="--- --- ---";
    if(st.st_mode & S_IRUSR)
        perm[0]='r';
    if(st.st_mode & S_IWUSR)
        perm[1]='w';
    if(st.st_mode & S_IXUSR)
        perm[2]='x';

    if(st.st_mode & S_IRGRP)
        perm[4]='r';
    if(st.st_mode & S_IWGRP)
        perm[5]='w';
    if(st.st_mode & S_IXGRP)
        perm[6]='x';

    if(st.st_mode & S_IROTH)
        perm[8]='r';
    if(st.st_mode & S_IWOTH)
        perm[9]='w';
    if(st.st_mode & S_IXOTH)
        perm[10]='x';

    printf("%s | %04o %s | %d-%02d-%02d %02d:%02d:%02d | %010ld bytes | %s\n",
           type[st.st_mode>>13],

           st.st_mode & 0777,
           perm,

           tm.tm_year+1900,
           tm.tm_mon+1,
           tm.tm_mday,
           tm.tm_hour,
           tm.tm_min,
           tm.tm_sec,

           st.st_size,

           name);
}

int main(int argc, char **argv){
    DIR *dp;
    struct stat st;
    if(argc==1){
        dp=opendir(".");
        if(!dp){
            perror("failed to open dir");
            return 1;
        }
        for(struct dirent *sd=readdir(dp);sd;sd=readdir(dp)){
            stat(sd->d_name, &st);
            print_info(st,sd->d_name);
        }
        return 0;
    }
    for(int i=1;i<argc;++i){
        stat(argv[i], &st);
        if(S_ISDIR(st.st_mode)){
            dp=opendir(argv[i]);
            for(struct dirent *sd=readdir(dp);sd;sd=readdir(dp)){
                stat(sd->d_name, &st);
                print_info(st,sd->d_name);
            }
        }
    }
    return 0;
}
