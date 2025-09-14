#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_SIZE 256

struct StringBuilder {
    char **data;
    size_t capacity;
    size_t item;
};

void init(struct StringBuilder *sb) {
    sb->data = (char **)malloc(256 * sizeof(char *));
    
    if(!sb->data) {
        puts("Error while allocating");
        return;
    }

    sb->item = 0;
    sb->capacity = INIT_SIZE;
}

void append(struct StringBuilder *sb, const char *data) {
    if (sb->data == NULL) init(sb);

    if(sb->item == sb->capacity) {
        sb->capacity *= 2;
        sb->data = realloc(sb->data, sb->capacity * sizeof(char *));
    }

    sb->data[sb->item++] = data;
}

static char **getString(struct StringBuilder *sb, size_t index) {
    if(index < array->size) {
        return array->data[index];
    } else {
        puts("ERROR: out of bounds");
        return NULL;
    }
}

int main(int argc, char*argv[]){
   // TODO: Parse le ./
   for (int i = 1 ; i < argc; ++i) {
       DIR *dir;
       char *file_path = argv[i];
       if ((dir = opendir(file_path)) == NULL) { // man opendir
           puts("ERROR: Could not open directory at the current dir");
           return 1;
       }
       struct dirent *de;
       while ((de = readdir(dir)) != NULL) { // man 2 readdir
           if(strcmp(de->d_name,"..") == 0 || strcmp(de->d_name,".") == 0) {
               continue;
           }
       }
   }
   return 0;
}
