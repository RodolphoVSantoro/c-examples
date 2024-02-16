#ifndef PRINT_ERR
#define PRINT_ERR

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void printerrf(char *format, ...) {
  printf("Logged error to ./error.log\n");
  va_list args;
  va_start(args, format);
  FILE *stream = fopen("error.log", "w");
  vfprintf(stream, format, args);
  fclose(stream);
  va_end(args);
}

#endif
