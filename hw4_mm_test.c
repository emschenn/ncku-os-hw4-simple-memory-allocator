#include "lib/hw_malloc.h"
#include "hw4_mm_test.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdint.h>
// void user_alloc(char *argv)
// {
//     char* arg = strtok(argv," ");
//     arg = strtok(NULL," ");
//     hw_malloc(atoi(arg));
// }
// void user_free(char *argv)
// {
//     char* arg = strtok(argv," ");
//     arg = strtok(NULL," ");
// }
// void user_print(char *argv)
// {
//     char* arg = strtok(argv," ");
//     arg = strtok(NULL," ");
//     if(strcmp(arg,"mmap_alloc_list")==0) {
//         print_list(mmap_alloc_list);
//     } else {

//     }
// }

int main(int argc, char *argv[])
{
    // char* line;
    // size_t len = 0;
    // ssize_t read_len;
    // heap_initial();
    printf("0x%012" PRIxPTR "\n",hw_malloc(17000));
    printf("0x%012" PRIxPTR "\n",hw_malloc(17000));
    //printf("%p\n",hw_malloc(17000));
    printf("%d",hw_free(0x000000000018));
    printf("%d",hw_free(0x000000008018));
    print_bin(bin[10]);
    // printf("%p\n",    hw_malloc(33768));
    // printf("%p\n",hw_malloc(37864));
    // printf("%p\n",hw_malloc(35816));
    // print_mmap(mmap_alloc_list);
    // while((getline(&line,&len,stdin)) != -1) {
    //     // if(read_len>0 && line[read_len-1] == '\n') {
    //     //     line[read_len-1] = '\0';
    //     //     read_len -= 1;
    //     // }
    //     if(strstr(line,"alloc")==0)
    //         user_alloc(line);
    //     else if(strstr(line,"free")==0)
    //         user_free(line);
    //     else if(strstr(line,"alloc")==0)
    //         user_print(line);
    //     printf("%s\n",line);
    // }


    char args[100];
    void *mem;
    int size;
    char list[20];
    while(scanf("%s",&args)!=EOF) {
        //printf("%s\n",args);
        if(strcmp(args,"alloc")==0) {
            scanf("%d",&size);
            printf("0x%012" PRIxPTR "\n",hw_malloc(size));
        } else if(strcmp(args,"free")==0) {
            scanf("%p",&mem);
            printf("%s\n",(hw_free(mem)==1?"success":"fail"));
        } else if(strcmp(args,"print")==0) {
            scanf("%s",&list);
            if(strcmp(list,"mmap_alloc_list")==0) {
                print_mmap(mmap_alloc_list);
            } else {
                if(strcmp(list,"bin[0]")==0)
                    print_bin(bin[0]);
                else if(strcmp(list,"bin[1]")==0)
                    print_bin(bin[1]);
                else if(strcmp(list,"bin[2]")==0)
                    print_bin(bin[2]);
                else if(strcmp(list,"bin[3]")==0)
                    print_bin(bin[3]);
                else if(strcmp(list,"bin[4]")==0)
                    print_bin(bin[4]);
                else if(strcmp(list,"bin[5]")==0)
                    print_bin(bin[5]);
                else if(strcmp(list,"bin[6]")==0)
                    print_bin(bin[6]);
                else if(strcmp(list,"bin[7]")==0)
                    print_bin(bin[7]);
                else if(strcmp(list,"bin[8]")==0)
                    print_bin(bin[8]);
                else if(strcmp(list,"bin[9]")==0)
                    print_bin(bin[9]);
                else if(strcmp(list,"bin[10]")==0)
                    print_bin(bin[10]);
            }
        }
    }
    return 0;
}
