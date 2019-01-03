#ifndef HW_MALLOC_H
#define HW_MALLOC_H
#include <unistd.h>
typedef struct chunk_info_t {
    size_t prev_chunk_size : 31;
    size_t current_chunk_size : 31;
    int allocated_flag : 1;
    int mmap_flag : 1;
} chunk_info_t;

typedef struct chunk_header *chunk_ptr_t;

typedef struct chunk_header {
    chunk_ptr_t prev;
    chunk_ptr_t next;
    chunk_info_t size_and_flag;
} chunk_header;

//chunk_header *heap;
chunk_header *bin[11];
chunk_header *mmap_alloc_list;

void heap_initial();
chunk_header* split(int size);
chunk_header* bin_popmin(int i);
chunk_header* bin_pop(int i);
void bin_push(int i,void *addr);
int size(int i);

chunk_header* mmap_create(void *addr,int size);
void mmap_list_sort(chunk_header* new);

chunk_header* bin_create(void *addr,int i);
void bin_list_sort(chunk_header* new,int i);
void *hw_malloc(size_t bytes);
int hw_free(void *mem);
void *hw_get_start_brk(void);

void print_mmap(chunk_header *list);
void print_bin(chunk_header *list);
#endif
