#include "meow-lang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

char buffer[256];
int console_module = 0;

char *trim(char *str);
void meow_lang_error(const char *line, const char *content);
void meow(const char *str);
void meowln(const char *str);
void compile_file(const char *file_name);

char *trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';
    return str;
}


void compile_file(const char *file_name) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("main.meow file not found ):");
    return;
  }

  while (fgets(buffer, sizeof(buffer), file)) {
    char *line = trim(buffer);

      if (strlen(line) == 0 || strncmp(line, "//", 2) == 0)
          continue;

      if (strcmp(line, "@import> CONSOLE") == 0) {
          if (console_module == 0) {
              console_module = 1;
          } else {
              meow_lang_error(line, "ERROR 001: This module already imported!");
          }
      }
      else if (strncmp(line, "meow> ", 6) == 0) {
          if (console_module == 1) {
              meow(line + 6);
          } else {
              meow_lang_error(line, "ERROR 002: CONSOLE module is not imported!");
          }
      }
      else if (strncmp(line, "meowln> ", 8) == 0) {
          if (console_module == 1) {
              meowln(line + 8);
          } else {
              meow_lang_error(line, "ERROR 002: CONSOLE module is not imported!");
          }
      }
      else {
          meow_lang_error(line, "ERROR 003: Unknown command!");
      }
  }

  fclose(file);
}

int main(void) {
  compile_file("src/main.meow");
}
