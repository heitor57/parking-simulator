#ifndef IO_H
#define IO_H
#define ENOENT 2 /* No such file or directory */
#define SUCCESS 1
#define FAIL 0
#include <stdio.h>
#include <stdbool.h>
#include "collission.h"
#include "object.h"
#include "time.h"
#define error(str, ...) {\
  fprintf(stderr,(str), ##__VA_ARGS__);\
  fprintf(stderr,"\n");\
  }
extern bool DEBUG;
void entry_read(int argc, char* argv[],FILE** fpc,FILE** fm);
int file_lines(FILE* f);
void print_collission_map(map cmap);
void print_algorithm_time(const algorithm_time *ai,FILE* f);
void obj_print(object* obj);
#endif
