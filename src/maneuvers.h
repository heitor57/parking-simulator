#ifndef MANEUVERS_H
#define MANEUVERS_H
#include "collission.h"
#include <stdio.h>
#include "hash.h"
int apply_maneuvers(FILE* fm,hash* objs,map coll_map);
int apply_maneuvers_perfect(FILE* fm,perfect_hash* objs,map coll_map);
#endif
