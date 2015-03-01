#include <stdio.h>
#include "ZZTHaloGametype.h"
#include "crc32.h"


uint32_t calculateGametypeChecksum(const void *gametype) {
    return 0xFFFFFFFF - crc32(0,gametype,0x98);
}

uint32_t calculateCEGametypeChecksum(const void *gametype) {
    return 0xFFFFFFFF - crc32(0,gametype,0xD8);
}

void convertCEGametypeToPC(void *gametype) {
    memcpy(gametype + 0x7C,gametype+0x9C,0x18);
    memset(gametype + 0x9C,0,0x18);
    memcpy(gametype + 0x94,gametype+0xD4,0x08);
    memset(gametype + 0xD4,0,0x08);
}

void convertPCGametypeToCE(void *gametype) {
    memcpy(gametype + 0xD4,gametype+0x94,0x08);
    memset(gametype + 0x94,0,0x08);
    memcpy(gametype + 0x9C,gametype+0x7C,0x18);
    memset(gametype + 0x7C,0,0x18);
}

void convertPCGametypeToHybrid(void *gametype) {
    memcpy(gametype + 0xD4,gametype + 0x94,0x08);
    memcpy(gametype + 0x9C,gametype + 0x7C,0x18);
}

