#ifndef HW_MALLOC_H
#define HW_MALLOC_H
#include <unistd.h>
typedef struct chunk_info_t {
    size_t prev_chunk_size : 31;
    size_t current_chunk_size : 31;
    int allocated_flag : 1;
    int mmap_flag : 1;
} chunk_info_t;

typedef void* chunk_ptr_t;

typedef struct chunk_header {
    chunk_ptr_t prev;
    chunk_ptr_t next;
    chunk_info_t size_and_flag;
} chunk_header;

chunk_header *heap;
chunk_header *bin[11];
chunk_header *mmap_alloc_list;
void heap_initial();
#endif
