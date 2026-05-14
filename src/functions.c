#include "meow-lang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

void meow_lang_error(const char *line, const char *content) {
  printf("%s\n%s", line, content);
  _getch();
  exit(0);
}

// console
void meow(const char *str) {
  printf("%s", str);
}

void meowln(const char *str) {
  printf("%s\n", str);
}
