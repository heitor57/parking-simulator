#ifndef COLLISSION_H
#define COLLISSION_H
#include "object.h"
#define Empty '0'
#define MAP_SIZE 6
typedef char point;
typedef point** map;
void clean_map(map map);
map init_map(void);
void free_map(map coll_map);
int collission_map_insert(map coll_map,object* obj);
int collission_map_remove(map coll_map,object* obj);
int collission_map_insert_persistent(map coll_map,object* obj);
#endif
