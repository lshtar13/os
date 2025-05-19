#include <string.h>
#ifndef __is_libk
#define __is_libk 1
#endif

#include <driver/driver.h>
#include <kernel/defs.h>
#include <kernel/interrupt.h>
#include <kernel/mem.h>
#include <kernel/timer.h>
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
  //  initMem();
  //  initInterrupt();
  //  initTimer(1);
  //  initDriver();

  //  char *c = (char *)kallocPage();
  //  strcpy(c, "yeah");
  //  printf("%p %s ", c, c);
  //  kfreePage(c);
  //  printf("%p %s ", c, c);
  printf("hello world!");

  for (;;)
    ;
}