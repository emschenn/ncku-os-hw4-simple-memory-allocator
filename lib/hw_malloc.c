#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include "hw_malloc.h"

#define mmap_threshold 32*1024
void* start_brk;

void heap_initial()
{
    start_brk = sbrk(64*1024);
    heap = start_brk + 0x00010000;
}


void *hw_malloc(size_t bytes)
{
    chunk_header *ptr;
    size_t size = bytes + sizeof(chunk_ptr_t);
    /*mmap allocation*/
    if(size > mmap_threshold) {
        if(size/1024 != 0)  size = (size/1024+1)*1024;
        void *addr;
        addr = mmap(0,size,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,0,0);
        mmap_push(addr,size);
    }
    /*heap allocation*/
    else {
        if(size < 32 || size == 32) {
            if(bin[0] == NULL) {

            }
            //ptr = pop(bin[0]);
        }
        // else if(size > 32 &&(size < 64 || size == 64))
        // else if(size > 64 &&(size < 128 || size == 128))
        // else if(size > 128 &&(size < 256 || size == 256))
        // else if(size > 256 &&(size < 512 || size == 512))
        // else if(size > 512 &&(size < 1024 || size == 1024))
        // else if(size > 1024 &&(size < 2048 || size == 2048))
        // else if(size > 2048 &&(size < 4096 || size == 4096))
        // else if(size > 4096 &&(size < 8192 || size == 8192))
        // else if(size > 8192 &&(size < 16384 || size == 16384))
        // else if(size > 16384 )
    }
    return NULL;
}

int hw_free(void *mem)
{
    chunk_header *ptr = mem;
    if(ptr->size_and_flag.mmap_flag = 1) {
        munmap(ptr,ptr->size_and_flag.current_chunk_size);
    } else {

    }
    return 0;
}

void *hw_get_start_brk(void)
{
    return NULL;
}

// void spilt(chunk_header *bin,int size)
// {
//     if(size == 10){
//         bin[10] = heap;
//         bin[10]->chunk_info_t->prev_chunk_size = 32768;
//         bin[10]->chunk_info_t->current_chunk_size = 32768;
//         bin[10]->chunk_info_t->allocated_flag = 0;
//         bin[10]->chunk_info_t->mmap_flag = 0;
//         bin[10]->prev = bin[10]->next = heap/2;
//         bin[10]->prev->chunk_info_t->prev_chunk_size = 32768;
//         bin[10]->prev->chunk_info_t->current_chunk_size = 32768;
//         bin[10]->prev->chunk_info_t->allocated_flag = 0;
//         bin[10]->prev->chunk_info_t->mmap_flag = 0;
//     }
//     else{
//         //if(bin[size++]!=NULL)
//     }
// }
// void bin_push(chunk_header *bin,void *addr,int size)
// {
//     chunk_header *element;
//     chunk_header *tail = bin->prev;
//     element = addr;
// 	element->prev = tail;
//     element->next = bin;
//     element->chunk_info_t->prev_chunk_size = size;
//     element->chunk_info_t->current_chunk_size = size;
//     element->chunk_info_t->allocated_flag = 0;
//     element->chunk_info_t->mmap_flag = 0;
//     tail->next = element;
//     bin->prev = element;
// }

void mmap_push(void *addr,int size)
{

    if(mmap_alloc_list == NULL) {
        mmap_alloc_list = addr;
        mmap_alloc_list->prev = NULL;
        mmap_alloc_list->next = NULL;
        //mmap_alloc_list->size_and_flag.prev_chunk_size = size;
        mmap_alloc_list->size_and_flag.current_chunk_size = size;
        mmap_alloc_list->size_and_flag.allocated_flag = 0;
        mmap_alloc_list->size_and_flag.mmap_flag = 1;
    } else {
        chunk_header *element;
        chunk_header *tail = mmap_alloc_list->prev;
        element = addr;
        element->prev = tail;
        element->next = mmap_alloc_list;
        element->size_and_flag.prev_chunk_size = size;
        element->size_and_flag.current_chunk_size = size;
        element->size_and_flag.allocated_flag = 0;
        element->size_and_flag.mmap_flag = 1;
        tail->next = element;
        mmap_alloc_list->prev = element;
    }

}

// void* bin_pop(chunk_header *bin)
// {
//     (bin->prev)->prev->next = (bin->prev)->next;
//     (bin->prev)->next->prev = (bin->prev)->prev;
//     bin->prev>chunk_info_t->allocated_flag = 1;
//     return (bin->prev);
// }

void print(chunk_header *list)
{
    while(list != NULL) {
        printf("%p",list);
        list = list->next;
    }
}