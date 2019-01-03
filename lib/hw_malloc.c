#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <stdint.h>
#include "hw_malloc.h"

#define mmap_threshold 32*1024
void* start_brk;
void* heap;
int initial_flag = 0;
void heap_initial()
{
    start_brk = sbrk(64*1024);
    heap = start_brk + 0x00010000;
    for(int i = 0; i<11; i++)
        bin[i] = NULL;
    //split(10);
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
        return(addr+sizeof(chunk_header));
    }
    /*heap allocation*/
    else {
        if(initial_flag == 0) {
            heap_initial();
            initial_flag = 1;
        }
        if(size < 32 || size == 32) {
            if(bin[0] == NULL)
                return((intptr_t)split(0)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(0)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 32 &&(size < 64 || size == 64)) {
            if(bin[1] == NULL)
                return((intptr_t)split(1)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(1)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 64 &&(size < 128 || size == 128)) {
            if(bin[2] == NULL)
                return((intptr_t)split(2)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(2)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 128 &&(size < 256 || size == 256)) {
            if(bin[3] == NULL)
                return((intptr_t)split(3)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(3)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 256 &&(size < 512 || size == 512)) {
            if(bin[4] == NULL)
                return((intptr_t)split(4)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(4)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 512 &&(size < 1024 || size == 1024)) {
            if(bin[5] == NULL)
                return((intptr_t)split(5)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(5)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 1024 &&(size < 2048 || size == 2048)) {
            if(bin[6] == NULL)
                return((intptr_t)split(6)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(6)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 2048 &&(size < 4096 || size == 4096)) {
            if(bin[7] == NULL)
                return((intptr_t)split(7)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(7)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 4096 &&(size < 8192 || size == 8192)) {
            if(bin[8] == NULL)
                return((intptr_t)split(8)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(8)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 8192 &&(size < 16384 || size == 16384)) {
            if(bin[9] == NULL)
                return((intptr_t)split(9)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
            else
                return( (intptr_t)bin_popmin(9)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        } else if(size > 16384 ) {
            if(bin[10] == NULL)
                split(10);
            return((intptr_t)bin_pop(10)+sizeof(chunk_header)-(intptr_t)hw_get_start_brk());
        }
    }
    return NULL;
}

int hw_free(void *mem)
{
    chunk_header *ptr = (intptr_t)mem - sizeof(chunk_header);
    if(ptr != NULL && ptr->size_and_flag.mmap_flag == 1) {
        munmap(ptr,ptr->size_and_flag.current_chunk_size);
        return 1;
    } else {
        ptr = (intptr_t)mem + (intptr_t)hw_get_start_brk()- sizeof(chunk_header);
        if(ptr->size_and_flag.current_chunk_size == 32) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,0);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 64) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,1);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 128) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,2);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 256) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,3);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 512) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,4);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 1024) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,5);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 2048) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,6);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 4096) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,7);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 8192) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,8);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 16384) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,9);
            return 1;
        } else if(ptr->size_and_flag.current_chunk_size == 32768) {
            ptr->size_and_flag.allocated_flag = 0;
            bin_list_sort(ptr,10);
            return 1;
        }
    }
    return 0;
}

void *hw_get_start_brk(void)
{
    return start_brk;
}

chunk_header* split(int i)
{
    chunk_header *temp;
    int j = i;
    if(i == 10) {
        // chunk_header *new = start_brk;
        // new->size_and_flag.prev_chunk_size = size(i);
        // new->size_and_flag.current_chunk_size = size(i);
        // new->size_and_flag.allocated_flag = 0;
        // new->size_and_flag.mmap_flag = 0;
        // new->prev = new->next = new;
        chunk_header * new1 = bin_create(start_brk,10);
        bin_list_sort(new1,10);
        // chunk_header *new2 = start_brk+size(10);
        // new->size_and_flag.prev_chunk_size = size(i);
        // new->size_and_flag.current_chunk_size = size(i);
        // new->size_and_flag.allocated_flag = 0;
        // new->size_and_flag.mmap_flag = 0;
        // new->prev = new->next = new;
        chunk_header *new2 = bin_create(start_brk+size(10),10);
        bin_list_sort(new2,10);
        //print_bin(bin[10]);
        //return bin_pop(10);
    } else {
        while(bin[j]==NULL)
            j++;
        temp = bin_popmin(j);
        bin_push(i,temp);
        bin_push(i,temp+size(i));
        return bin_popmin(i);
    }
}
chunk_header *split(int i)
{
    if (bin[i]->chunk_size - size(i) >= 48) {
        chunk_header *base = *ori;
        /*Change next chunk's prev_chunk_size*/
        chunk_header *nxt = (chunk_header *)((intptr_t)(void*)base +(intptr_t)(void*)((chunk_header *)base)->chunk_size);
        nxt->prev_chunk_size -= need;
        /*Create upper chunk by shifting need*/
        chunk_header *new = (void *)((intptr_t)(void*)base + need);
        new->chunk_size = (base)->chunk_size - need;
        new->prev_chunk_size = need;
        new->prev_free_flag = 0;
        bin[i] = new;
        chunk_header *ret = create_chunk(base, need);
        /*Insert upper chunk into bin*/
        en_bin(search_enbin((bin[i])->chunk_size), (bin[i]));
        slice_num++;
        return ret;
    } else {
        /*If chunk size is not enough to split, return whole chunk*/
        chunk_header *nxt = (chunk_header *)((intptr_t)(void*)(*ori) +(intptr_t)(void*)((chunk_header *)(*ori))->chunk_size);
        nxt->prev_free_flag = 0;
        return (*ori);
    }
}
void bin_push(int i,void *addr)
{
    if(bin[i] == NULL) {
        bin[i] = addr;
        bin[i]->size_and_flag.prev_chunk_size = size(i);
        bin[i]->size_and_flag.current_chunk_size = size(i);
        bin[i]->size_and_flag.allocated_flag = 0;
        bin[i]->size_and_flag.mmap_flag = 0;
        bin[i]->prev = bin[i]->next = bin[i];
    } else {
        chunk_header *last = bin[i]->prev;
        chunk_header *new = addr;
        new->size_and_flag.current_chunk_size = size(i);
        new->size_and_flag.prev_chunk_size = size(i);
        new->size_and_flag.allocated_flag = 0;
        new->size_and_flag.mmap_flag = 0;
        new->next = bin[i];
        new->prev = last;
        last->next = bin[i]->prev = new;
        bin[i] = new;
    }
}

chunk_header* bin_popmin(int i)
{
    if(bin[i] == NULL)
        return NULL;
    chunk_header *temp = bin[i];
    chunk_header *prev1;
    chunk_header *min = bin[i];
    printf("min: %p\n",min);
    while(temp->next != bin[i]) {
        printf("%p\n",temp);
        if(temp < min) {
            min = temp;
        }
        prev1 = temp->prev;
        temp = temp->next;
    }
    printf("min: %p\n",min);
    if(min->next == bin[i]) {   //only 1
        bin[i] = NULL;
        return min;
    }
    if(min == bin[i]) { //first node
        prev1 = bin[i]->prev;
        bin[i] = bin[i]->next;
        prev1->next = bin[i];
        bin[i]->prev = prev1;
    } else if(min->next == bin[i]) { //last node
        prev1->next = bin[i];
        bin[i]->prev = prev1;
    } else {
        chunk_header *temp1 = min->next;
        prev1->next = temp1;
        temp1->prev = prev1;
    }
    return min;
}
chunk_header* bin_pop(int i)
{
    if(bin[i]==NULL)
        return NULL;
    if(bin[i]->next == bin[i]) { //only 1 node
        chunk_header *new = bin[i];
        bin[i] = NULL;
        new->size_and_flag.allocated_flag = 1;
        return new;
    } else {
        chunk_header *new = bin[i];
        bin[i]->prev->next = bin[i]->next;
        bin[i]->next->prev = bin[i]->prev;
        bin[i] = bin[i]->next;
        new->prev = new->next = new;
        new->size_and_flag.allocated_flag = 1;
        return new;
    }
}

chunk_header* bin_create(void *addr,int i)
{
    chunk_header *new = addr;
    new->size_and_flag.prev_chunk_size = size(i);
    new->size_and_flag.current_chunk_size = size(i);
    new->size_and_flag.allocated_flag = 0;
    new->size_and_flag.mmap_flag = 0;
    new->prev = new->next = new;
    return new;
}

void bin_list_sort(chunk_header* new,int i)
{
    chunk_header* temp;
    if(bin[i] == NULL) {
        new->next = new;
        new->prev = new;
        bin[i] = new;
    } else if(bin[i] > new) {
        new->next = bin[i];
        new->prev = bin[i]->prev;
        new->next->prev = new;
        new->prev->next = new;
        bin[i] = new;
    } else {
        temp = bin[i];
        while(temp->next != bin[i] && temp->next < new)
            temp = temp->next;
        new->next = temp->next;
        temp->next = new;
        new->next->prev = new;
        new->prev = temp;
    }
}

chunk_header* mmap_create(void *addr,int size)
{
    chunk_header *new = addr;
    new->size_and_flag.current_chunk_size = size;
    new->size_and_flag.allocated_flag = 1;
    new->size_and_flag.mmap_flag = 1;
    new->prev = new->next = new;
    return new;
}

void mmap_list_sort(chunk_header* new)
{
    chunk_header* temp;
    if(mmap_alloc_list == NULL) {
        new->next = new;
        new->prev = new;
        mmap_alloc_list = new;
    } else if(mmap_alloc_list->size_and_flag.current_chunk_size >= new->size_and_flag.current_chunk_size) {
        new->next = mmap_alloc_list;
        new->prev = mmap_alloc_list->prev;
        new->next->prev = new;
        new->prev->next = new;
        new->size_and_flag.prev_chunk_size = new->prev->size_and_flag.current_chunk_size;
        new->next->size_and_flag.prev_chunk_size = new->size_and_flag.current_chunk_size;
        mmap_alloc_list = new;
    } else {
        temp = mmap_alloc_list;
        while(temp->next != mmap_alloc_list && temp->next->size_and_flag.current_chunk_size < new->size_and_flag.current_chunk_size)
            temp = temp->next;
        new->next = temp->next;
        temp->next = new;
        new->next->prev = new;
        new->prev = temp;
        new->size_and_flag.prev_chunk_size = temp->size_and_flag.current_chunk_size;
        new->next->size_and_flag.prev_chunk_size = new->size_and_flag.current_chunk_size;
    }
}


void print_mmap(chunk_header *list)
{
    chunk_header *temp = list;
    if(list != NULL) {
        while(temp->next != list) {
            printf("%p--------%d\n",temp,temp->size_and_flag.current_chunk_size);
            temp = temp->next;
        }
        printf("%p--------%d\n",temp,temp->size_and_flag.current_chunk_size);
    }
}


void print_bin(chunk_header *list)
{
    chunk_header *temp = list;
    if(list != NULL) {
        while(temp->next != list) {
            printf("0x%012" PRIxPTR "-------%d\n",(uintptr_t)temp-(intptr_t)hw_get_start_brk(),temp->size_and_flag.current_chunk_size);
            temp = temp->next;
        }
        printf("0x%012" PRIxPTR "-------%d\n",(uintptr_t)temp-(intptr_t)hw_get_start_brk(),temp->size_and_flag.current_chunk_size);
    }
}


int size(int i)
{
    int size = 32;
    for(int j = 0; j<i; j++)
        size = size*2;
    return size;
}

