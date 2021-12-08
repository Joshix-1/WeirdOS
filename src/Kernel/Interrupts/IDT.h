#ifndef WEIRDOS_IDT_H
#define WEIRDOS_IDT_H

struct IDT64{
    unsigned short offset_low;
    unsigned short selector;
    unsigned char ist;
    unsigned char types_attr;
    unsigned short offset_mid;
    unsigned int offset_high;
    unsigned int zero;
};

void InitializeIDT();
void InitializeFaults();

#endif