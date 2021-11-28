#include "Heap.h"

void Heap::InitializeHeap(long long heapAddress, long long HeapLength){
  FirstFreeMemorySegment = (MemorySegmentHeader*)heapAddress;
  FirstFreeMemorySegment->MemoryLength = HeapLength - sizeof(MemorySegmentHeader);
  FirstFreeMemorySegment->NextSegment = 0;
  FirstFreeMemorySegment->PreviousSegment = 0;
  FirstFreeMemorySegment->NextFreeSegment = 0;
  FirstFreeMemorySegment->PreviousFreeSegment = 0;
  FirstFreeMemorySegment->free = true;
}

void* Heap::calloc(long long size){
    void* mallocVal = malloc(size);
    memset(mallocVal, 0, size);
    return mallocVal;
}

void* Heap::calloc(long long num, long long size){
    return calloc(num * size);
}

void* Heap::malloc(long long size){
  long long remainder = size % 8;
  size -= remainder;
  if (remainder != 0){
    size += 8;
  }
  MemorySegmentHeader* currentMemorySegment = FirstFreeMemorySegment;

  while (true){
    if (currentMemorySegment->MemoryLength >= size){

      if(currentMemorySegment->MemoryLength > size + sizeof(MemorySegmentHeader)){
        MemorySegmentHeader* newSegmentHeader = (MemorySegmentHeader*)((long long)currentMemorySegment + sizeof(MemorySegmentHeader) + size);
        newSegmentHeader->free = true;
        newSegmentHeader->MemoryLength = ((long long)currentMemorySegment->MemoryLength) - (sizeof(MemorySegmentHeader) + size);
        newSegmentHeader->NextFreeSegment = currentMemorySegment->NextFreeSegment;
        newSegmentHeader->NextSegment = currentMemorySegment->NextSegment;
        newSegmentHeader->PreviousSegment = currentMemorySegment;
        newSegmentHeader->PreviousFreeSegment = currentMemorySegment->PreviousFreeSegment;

        currentMemorySegment->NextFreeSegment = newSegmentHeader;
        currentMemorySegment->NextSegment = newSegmentHeader;
        currentMemorySegment->MemoryLength = size;
      }
      if (currentMemorySegment == FirstFreeMemorySegment){
        FirstFreeMemorySegment = currentMemorySegment->NextFreeSegment;
      }
      currentMemorySegment->free = false;

      if (currentMemorySegment->PreviousFreeSegment != 0){
        currentMemorySegment->PreviousFreeSegment->NextFreeSegment = currentMemorySegment->NextFreeSegment;
      }
      if (currentMemorySegment->NextFreeSegment != 0){
        currentMemorySegment->NextFreeSegment->PreviousFreeSegment = currentMemorySegment->PreviousFreeSegment;
      }
      if (currentMemorySegment->PreviousSegment != 0){
          currentMemorySegment->PreviousSegment->NextFreeSegment = currentMemorySegment->NextFreeSegment;
      }
      if (currentMemorySegment->NextSegment != 0){
          currentMemorySegment->NextSegment->PreviousFreeSegment->NextFreeSegment = currentMemorySegment->PreviousFreeSegment;
      }

      return currentMemorySegment + 1;
    }
    if (currentMemorySegment->NextFreeSegment == 0){
        return 0;
    }
    currentMemorySegment = currentMemorySegment->NextFreeSegment;
  }
  return 0;
}

void* Heap::realloc(void* address, long long newSize){
    MemorySegmentHeader* oldSegmentHeader;

    AlignedMemorySegmentHeader* AMSH = (AlignedMemorySegmentHeader*)address -1;
    if (AMSH->IsAligned){
        oldSegmentHeader = (MemorySegmentHeader*)AMSH->MemorySegmentHeaderAddress;
    }
    else{
        oldSegmentHeader = ((MemorySegmentHeader*)address) - 1;
    }
    long long smallerSize = newSize;
    if (oldSegmentHeader->MemoryLength < newSize){
        smallerSize = oldSegmentHeader->MemoryLength;
    }
    void* newMem = malloc(newSize);
    memcpy(newMem, address, smallerSize);
    free(address);
    return newMem;
}

void Heap::CombineFreeSegments(MemorySegmentHeader* a, MemorySegmentHeader* b){
    if (a == 0) return;
    if (b == 0) return;
    if (a < b){
        a->MemoryLength += b->MemoryLength + sizeof(MemorySegmentHeader);
        a->NextSegment = b->NextSegment;
        a->NextFreeSegment = b->NextFreeSegment;
        b->NextSegment->PreviousSegment = a;
        b->NextSegment->PreviousFreeSegment = a;
        b->NextFreeSegment->PreviousFreeSegment = a;
    }
    else{
        b->MemoryLength += a->MemoryLength + sizeof(MemorySegmentHeader);
        b->NextSegment = a->NextSegment;
        b->NextFreeSegment = a->NextFreeSegment;
        a->NextSegment->PreviousSegment = b;
        a->NextSegment->PreviousFreeSegment = b;
        a->NextFreeSegment->PreviousFreeSegment = b;
    }
}

void Heap::free(void* address){
    MemorySegmentHeader* currentMemorySegment;

    AlignedMemorySegmentHeader* AMSH = (AlignedMemorySegmentHeader*)address -1;
    if (AMSH->IsAligned){
        currentMemorySegment = (MemorySegmentHeader*)AMSH->MemorySegmentHeaderAddress;
    }
    else{
        currentMemorySegment = ((MemorySegmentHeader*)address) - 1;
    }
    currentMemorySegment->free = true;

    if (currentMemorySegment < FirstFreeMemorySegment){
        FirstFreeMemorySegment = currentMemorySegment;
    }
    if (currentMemorySegment->NextFreeSegment != 0){
        if (currentMemorySegment->NextFreeSegment->PreviousFreeSegment < currentMemorySegment){
            currentMemorySegment->NextFreeSegment->PreviousFreeSegment = currentMemorySegment;
        }
    }
    if (currentMemorySegment->PreviousFreeSegment != 0){
        if (currentMemorySegment->PreviousFreeSegment->NextFreeSegment > currentMemorySegment){
            currentMemorySegment->PreviousFreeSegment->NextFreeSegment = currentMemorySegment;
        }
    }
    if (currentMemorySegment->NextSegment != 0){
        currentMemorySegment->NextSegment->PreviousSegment = currentMemorySegment;
        if (currentMemorySegment->NextSegment->free){
            CombineFreeSegments(currentMemorySegment, currentMemorySegment->NextSegment);
        }
    }
    if (currentMemorySegment->PreviousSegment != 0){
        currentMemorySegment->PreviousSegment->NextSegment = currentMemorySegment;
        if (currentMemorySegment->PreviousSegment->free){
            CombineFreeSegments(currentMemorySegment, currentMemorySegment->PreviousSegment);
        }
    }
}

void* Heap::aligned_alloc(long long allignment, long long size){
    long long allignmentRemainder = allignment % 8;
    allignment -= allignmentRemainder;
    if (allignmentRemainder != 0){
        allignment += 8;
    }

    long long sizeRemainder = size % 8;
    size -= sizeRemainder;
    if (sizeRemainder != 0){
        size += 8;
    }

    long long fullsize = size + allignment;

    void* mallocVal = malloc(fullsize);
    long long address = (long long)mallocVal;

    long long remainder = address % allignment;
    address -= remainder;
    if (remainder != 0){
        address += allignment;

        AlignedMemorySegmentHeader* AMSH = (AlignedMemorySegmentHeader*)address - 1;
        AMSH->IsAligned = true;
        AMSH->MemorySegmentHeaderAddress = (long long)mallocVal - sizeof(MemorySegmentHeader);
    }

    return (void*)address;
}
