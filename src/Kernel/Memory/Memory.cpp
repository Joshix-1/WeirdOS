#include "Memory.h"

void memset(void* start, long long value, long long num){

    if (num <= 8){
        unsigned char* valPtr = (unsigned char*)&value;
        for (unsigned char* ptr = (unsigned char*)start; ptr < (unsigned char*)((long long)start + num); ptr++){
            *ptr = *valPtr;
            valPtr++;
        }

        return;
    }

    long long proceedingBytes = num % 8;
    long long newnum = num -proceedingBytes;

    for (long long* ptr = (long long*)start; ptr < (long long*)((long long)start + newnum); ptr++){
        *ptr = value;
    }

    unsigned char* valPtr = (unsigned char*)&value;
    for (unsigned char* ptr = (unsigned char*)((long long)start + newnum); ptr < (unsigned char*)((long long)start + num); ptr++){
        *ptr = *valPtr;
        valPtr++;
    }
}

void memcpy(void*destination, void* source, long long num){
    if (num <= 8){
        unsigned char* valPtr = (unsigned char*)source;
        for (unsigned char* ptr = (unsigned char*)destination; ptr < (unsigned char*)((long long)destination + num); ptr++){
            *ptr = *valPtr;
            valPtr++;
        }

        return;
    }

    long long proceedingBytes = num % 8;
    long long newnum = num -proceedingBytes;
    long long* srcptr = (long long*)source;

    for (long long* destptr = (long long*)destination; destptr < (long long*)((long long)destination + newnum); destptr++){
        *destptr = *srcptr;
        srcptr++;
    }

    unsigned char* srcptr8 = (unsigned char*)((long long)source + newnum);
    for (unsigned char* destptr8 = (unsigned char*)((long long)destination + newnum); destptr8 < (unsigned char*)((long long)destination + num); destptr8++){
        *destptr8 = *srcptr8;
        srcptr8++;
    }
}

int memcmp(const void* aptr, const void* bptr, long unsigned int size) {
    const unsigned char* a = (const unsigned char*) aptr;
    const unsigned char* b = (const unsigned char*) bptr;
    for (long unsigned int i = 0; i < size; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}