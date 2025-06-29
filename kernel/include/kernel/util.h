#ifndef __INCLUDE_KERNEL_UTIL_H
#define __INCLUDE_KERNEL_UTIL_H 1

#define BITMAP(name, nbit) uint32_t name[nbit / 32 + nbit % 32]
#define ISUSED(bitmap, bit) (bitmap[bit / 32] & (1 << (bit % 32)))
#define USE(bitmap, bit) (bitmap[bit / 32] |= (1 << bit % 32))

#endif