#include "frame.h"
#include <kernel/mem.h>

#include <stdint.h>
#include <string.h>

static struct pframe_t frames;

static inline void useFrame(uint32_t idx) {
  frames.bitmap[idx / 32] |= (1 << idx % 32);
}

static inline void unuseFrame(uint32_t idx) {
  frames.bitmap[idx / 32] &= ~(1 << (idx % 32));
}

static inline uint32_t isusedFrame(uint32_t idx) {
  return frames.bitmap[idx / 32] & (1 << (idx % 32));
}

uint32_t kallocFrame() {
  uint32_t fidx = frames.lastIdx;
  for (; isusedFrame(fidx); ++fidx) {
    if (fidx == MAX_FRAMES) {
      return NO_AVAIL_FRAME;
    }
  }

  useFrame(fidx);
  frames.lastIdx = fidx;

  return fidx * FRAME_SIZE;
}

void kfreeFrame(uint32_t paddr) {
  uint32_t fidx = paddr / FRAME_SIZE;
  unuseFrame(fidx);
  frames.lastIdx = fidx;
}

void initFrames(uint32_t ptr) {
  memset(frames.bitmap, 0, sizeof(uint32_t) * N_BITMAP_ENTRY);
  frames.start = (ptr / FRAME_SIZE + 1) * FRAME_SIZE;
  for (uint32_t fidx = 0; fidx * FRAME_SIZE <= frames.start; ++fidx) {
    useFrame(fidx);
    frames.lastIdx = fidx;
  }
}