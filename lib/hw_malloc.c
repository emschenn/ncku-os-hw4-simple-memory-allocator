#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include "hw_malloc.h"

#define mmap_threshold 32*1024
void* start_brk;
void* heap;
void heap_initial()
{
    start_brk = sbrk(64*1024);
    heap = start_brk + 0x00010000;
    spilt(10);
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
        chunk_header* new = mmap_create(addr,size);
        mmap_list_sort(new);
        printf("%p\n",addr+24);
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
        return 1;
    } else {

    }
    return 0;
}

void *hw_get_start_brk(void)
{
    return start_brk;
}

chunk_header* spilt(int size)
{
    if(size == 10) {
        bin[10] = start_brk;
        bin[10]->size_and_flag.prev_chunk_size = 32*1024;
        bin[10]->size_and_flag.current_chunk_size = 32*1024;
        bin[10]->size_and_flag.allocated_flag = 0;
        bin[10]->size_and_flag.mmap_flag = 0;
        bin[10]->prev = bin[10]->next = start_brk+32*1024;
        bin[10]->prev->size_and_flag.prev_chunk_size = 32*1024;
        bin[10]->prev->size_and_flag.current_chunk_size = 32*1024;
        bin[10]->prev->size_and_flag.allocated_flag = 0;
        bin[10]->prev->size_and_flag.mmap_flag = 0;
        return bin[10];
    } else {
        //if(bin[size++]!=NULL)
    }
}
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

chunk_header* mmap_create(void *addr,int size)
{
    chunk_header *new = addr;
    new->size_and_flag.current_chunk_size = size;
    new->size_and_flag.allocated_flag = 1;
    new->size_and_flag.mmap_flag = 1;
    new->prev = new->next = NULL;
    return new;
}

void mmap_list_sort(chunk_header* new)
{
    chunk_header* temp;
    if(mmap_alloc_list == NULL)
        mmap_alloc_list = new;
    else if(mmap_alloc_list->size_and_flag.current_chunk_size >= new->size_and_flag.current_chunk_size) {
        new->next = mmap_alloc_list;
        new->next->prev = new;
        new->next->size_and_flag.prev_chunk_size = new->size_and_flag.current_chunk_size;
        mmap_alloc_list = new;
    } else {
        temp = mmap_alloc_list;
        while(temp->next != NULL && temp->next->size_and_flag.current_chunk_size < new->size_and_flag.current_chunk_size)
            temp = temp->next;
        new->next = temp->next;
        if(temp->next != NULL) {
            new->next->prev = new;
            new->next->size_and_flag.prev_chunk_size = new->size_and_flag.current_chunk_size;
        }
        temp->next = new;
        new->prev = temp;
        new->size_and_flag.prev_chunk_size = temp->size_and_flag.current_chunk_size;
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
        printf("%p--------%d\n",list,list->size_and_flag.current_chunk_size);
        list = list->next;
    }
}