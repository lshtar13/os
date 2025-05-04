#ifndef __is_libk
#define __is_libk 1
#endif

#include <kernel/interrupt.h>
#include <kernel/mem.h>
#include <kernel/tty.h>
#include <stdio.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if defined(__i386__)
#endif

void kernel_main(void) {
  initMem();
  initInterrupt();
  printf("hello world!");
  initTimer(1);

  for (;;)
    ;
}