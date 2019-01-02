#include "lib/hw_malloc.h"
#include "hw4_mm_test.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
void user_alloc(char *argv)
{
    char* arg = strtok(argv," ");
    arg = strtok(NULL," ");
    //hw_malloc(atoi(arg));

}
void user_free(char *argv)
{
    char* arg = strtok(argv," ");
    arg = strtok(NULL," ");
    printf("%s",arg);
}
void user_print(char *argv)
{
    char* arg = strtok(argv," ");
    arg = strtok(NULL," ");
    if(strcmp(arg,"mmap_alloc_list")==0) {

    } else {

    }
}

int main(int argc, char *argv[])
{
    char* line;
    size_t len = 0;
    ssize_t read_len;
    heap_initial();
    //hw_malloc(33768);
    hw_malloc(37864);
    print(mmap_alloc_list);
    while((read_len = getline(&line,&len,stdin)) != -1) {
        if(read_len>0 && line[read_len-1] == '\n') {
            line[read_len-1] = '\0';
            read_len -= 1;
        }
        if(strstr(line,"alloc")==0)
            user_alloc(line);
        else if(strstr(line,"free")==0)
            user_free(line);
        else if(strstr(line,"alloc")==0)
            user_print(line);
    }
    //fscanf(stdin,"%s",&str);
    //printf("%s",str);
    // f = fopen("outputfile.txt","w");
    // if(f == NULL)
    //     printf("error");
    // user_loop();
    // fclose(f);
    return 0;
}
