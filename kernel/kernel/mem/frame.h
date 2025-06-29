#ifndef __KERNEL_FRAME_H_
#define __KERNEL_FRAME_H_ 1

#include <stdint.h>

#define FRAME_SIZE 0x1000
#define MAX_FRAMES 0x100000
#define N_BITMAP_ENTRY (MAX_FRAMES / 32 + 1)
#define NO_AVAIL_FRAME 0

#define FRAME_USE(bitmap, idx) (bitmap[idx / 32] |= (1 << idx % 32))
#define FRAME_UNUSE(bitmap, idx) (bitmap[idx / 32] &= ~(1 << (idx % 32)))
#define FRAME_ISUSED(bitmap, idx) (bitmap[idx / 32] & (1 << (idx % 32)))

struct pframe_t {
  uint32_t start;
  uint32_t bitmap[N_BITMAP_ENTRY], lastIdx;
};

#endif