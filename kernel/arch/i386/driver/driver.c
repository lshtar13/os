#include "keyboard/keyboard.h"
#include <driver/driver.h>
#include <driver/tty.h>

void initDriver() {
  terminal_initialize();
  initKeyboard();
}