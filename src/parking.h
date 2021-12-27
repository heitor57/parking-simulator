#ifndef PARKING_H
#define PARKING_H
#include "hash.h"
#include "collission.h"
#include <stdio.h>
int parking_init(FILE* fpc,hash* objs,map coll_map);
int parking_init_perfect(FILE* fpc,perfect_hash* objs,map coll_map);
#endif
