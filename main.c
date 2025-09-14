#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

static void print_info(struct stat st,const char *name){
    struct tm tm=*localtime(&st.st_mtime);
    printf("%04o %d-%02d-%02d %02d:%02d:%02d %ld %s\n",
           st.st_mode & 0777,

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
