#ifndef WEIRDOS_HEAP_H
#define WEIRDOS_HEAP_H

#include "Memory.h"

// Header of MemorySegment which is used in linked list
struct MemorySegmentHeader {
  long long MemoryLength;
  MemorySegmentHeader* NextSegment;
  MemorySegmentHeader* PreviousSegment;
  MemorySegmentHeader* NextFreeSegment;
  MemorySegmentHeader* PreviousFreeSegment;
  bool free;
};

struct AlignedMemorySegmentHeader{
    long long MemorySegmentHeaderAddress : 63;
    bool IsAligned : 1;
};

// The real magic of Heap
class Heap{
    private:
    MemorySegmentHeader* FirstFreeMemorySegment;
    void* calloc(long long num, long long size);
    void CombineFreeSegments(MemorySegmentHeader* a, MemorySegmentHeader* b);

    public:
    void InitializeHeap(long long heapAddress, long long HeapLength);
    void* calloc(long long size);
    void* malloc(long long size);
    void* realloc(void* address, long long newSize);
    void free(void* address);
    void* aligned_alloc(long long allignment, long long size);
};

#endif