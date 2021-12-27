#ifndef HASH_H
#define HASH_H
#include "object.h"

typedef struct hash hash;

hash* new_hash(int TABLE_SIZE);
void free_hash(hash* ha);
int to_string_hash(char *str);
int insert_hash(hash* ha,const object* obj);
int search_hash(const hash* ha, char label,const object** obj);


#define HASH_IN_SIZE 16
typedef struct perfect_hash perfect_hash;
perfect_hash* new_perfect_hash(int TABLE_SIZE);
void free_perfect_hash(perfect_hash* perf_hash);
int insert_perfect_hash(perfect_hash* perf_hash,const object* obj);
int search_perfect_hash(perfect_hash* perf_hash,char label,const object** obj);

#endif
