#ifndef __is_libk
#define __is_libk 1
#endif

#include <stdio.h>
#include <kernel/tty.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

__attribute__ ((constructor)) void kernel_early_main(void)
{
	terminal_initialize();
	printf("11111111111111111111111111111111111111111111111!\n");
}

void kernel_main(void) 
{
	printf("Hello, kernel World!\n");
}