#include <stdlib.h>
#include <stdio.h>

void usage(char *prog_name)
{
  fprintf(stderr, "usage: %s [<number of threads>]\n", prog_name);
  fprintf(stderr, "If <number of threads> is omitted, the program will\n");
  fprintf(stderr, "launch one thread per available CPU core.\n");
  exit(0);
}
