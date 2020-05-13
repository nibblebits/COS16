#include "kheap.h"
#include "heap.h"
static struct heap* kheap;

void kheap_init()
{
    // Our kernel heap should be just after the stack
    kheap = heap_create(COS16_STACK_END_ADDRESS);   
}

void* kmalloc(int size)
{
    return heap_malloc(kheap, size);
}

void kfree(void* ptr)
{
    return heap_free(kheap, ptr);
}