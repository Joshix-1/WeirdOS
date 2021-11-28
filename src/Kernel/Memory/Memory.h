#pragma once

// Basic Memory Operations
void memset(void* start, long long value, long long num);
void memcpy(void* destination, void* source, long long num);    // Copy Memory Segment over other Memory Segment
int memcmp(const void* aptr, const void* bptr, long unsigned int size);