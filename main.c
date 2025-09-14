#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char*argv[]){
    DIR *dir;
    // Better handeling of the path naming honestly
    if (argv[1] == NULL) {
        argv[1] = ".";
        argc = 2;
   }
   // TODO parse multiple arguments
    if (argc <= 1) {
         puts("UR MOM");
         return 1;
    }
    // TODO: Parse le ./
    for (int i = 1 ; i < argc; ++i) {
        char *file_path = argv[i];
        if (strcmp(argv[0], "./lsode") == 0) {
            if ((dir = opendir(file_path)) == NULL) { // man opendir
                puts("ERROR: Could not open directory at the current dir");
                return 1;
            }
        }

        struct dirent *de;
        printf("%s\n", file_path);
        while ((de = readdir(dir)) != NULL) { // man 2 readdir
            if(strcmp(de->d_name,"..") == 0 || strcmp(de->d_name,".") == 0) {
                continue;
            }
            printf("%s\n", de->d_name);
        }
        printf("\n");
    }
    return 0;
}
