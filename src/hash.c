#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include "io.h"

struct hash{
  int qtd, TABLE_SIZE;
   object **objs;
};

hash* new_hash(int TABLE_SIZE){
  hash* ha = (hash*) malloc(sizeof(hash));
  if(ha != NULL){
    ha->TABLE_SIZE = TABLE_SIZE;
    ha->objs = ( object**) calloc(TABLE_SIZE , sizeof( object*));
    if(ha->objs == NULL){
      free(ha);
      return NULL;
    }
    ha->qtd = 0;
  }
  return ha;
}

void free_hash(hash* ha){
  if(ha != NULL){
    int i;
    for(i=0; i < ha->TABLE_SIZE; i++){
      if(ha->objs[i] != NULL)
	free(ha->objs[i]);
    }
    free(ha->objs);
    free(ha);
  }
}

int to_string_hash(char *str){
  int i, valor = 7;
  int tam = strlen(str);
  for(i=0; i < tam; i++)
    valor = 31 * valor + (int) str[i];
  return (valor & 0x7FFFFFFF);
}


int linear_probing(int pos, int i, int TABLE_SIZE){
  return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

int key_division(int key, int TABLE_SIZE){
    return (key & 0x7FFFFFFF) % TABLE_SIZE;
}

int insert_hash(hash* ha,const object* obj){
  if(ha == NULL || ha->qtd == ha->TABLE_SIZE)
    return FAIL;

  int key = obj_get_label(obj);

  int i, pos, newPos;
  pos = key_division(key,ha->TABLE_SIZE);
  for(i=0; i < ha->TABLE_SIZE; i++){
    newPos = linear_probing(pos,i,ha->TABLE_SIZE);

    if(ha->objs[newPos] == NULL){
       object* new;
       new = new_object();
      if(new == NULL)
	return FAIL;
      object_cpy(new,obj);
      ha->objs[newPos] = new;
      ha->qtd++;
      return SUCCESS;
    }else if(obj_get_label(ha->objs[newPos]) == obj_get_label(obj)){
      return FAIL;
    }
  }
  return FAIL;
}

int search_hash(const hash* ha, char label,const object** obj){
  if(ha == NULL)
    return 0;

  int i, pos, newPos;
  pos = key_division(label,ha->TABLE_SIZE);
  for(i=0; i < ha->TABLE_SIZE; i++){
    newPos = linear_probing(pos,i,ha->TABLE_SIZE);

    if(ha->objs[newPos] == NULL)
      return 0;

    if(obj_get_label(ha->objs[newPos]) == label){
      *obj= ha->objs[newPos];
      return 1;
    }
  }
  return 0;
}







struct perfect_hash{
  int TABLE_SIZE;
  hash** hashs;
};
int hash_division(int key,int TABLE_SIZE){
  return key/TABLE_SIZE;
}

perfect_hash* new_perfect_hash(int TABLE_SIZE){
  perfect_hash* perf_hash = malloc(sizeof(perfect_hash));
  if(perf_hash != NULL){
    int i;
    perf_hash->TABLE_SIZE = TABLE_SIZE;
    perf_hash->hashs = malloc(TABLE_SIZE*sizeof(hash*));
    if(perf_hash->hashs == NULL){
      free(perf_hash);
      return NULL;
    }
    for(i=0; i < perf_hash->TABLE_SIZE; i++)
      perf_hash->hashs[i] = NULL;
    // most used characters seem to be A to Z in ascii table so malloc now
    perf_hash->hashs[hash_division('A',TABLE_SIZE)]= new_hash(TABLE_SIZE);
    perf_hash->hashs[hash_division('Z',TABLE_SIZE)]= new_hash(TABLE_SIZE);
  }
  return perf_hash;
}

void free_perfect_hash(perfect_hash* perf_hash){
  if(perf_hash != NULL){
    int i;
    for(i=0; i < perf_hash->TABLE_SIZE; i++){
      if(perf_hash->hashs[i] != NULL){
	free_hash(perf_hash->hashs[i]);
      }
    }
    free(perf_hash->hashs);
    free(perf_hash);
  }
}

int insert_perfect_hash(perfect_hash* perf_hash,const object* obj){
  if(perf_hash == NULL || perf_hash->hashs == NULL)
    return FAIL;

  int key = obj_get_label(obj);

  int hash_index = hash_division(key,perf_hash->TABLE_SIZE),
    obj_index = key_division(key,perf_hash->TABLE_SIZE);

  if(perf_hash->hashs[hash_index] == NULL){
    perf_hash->hashs[hash_index] = new_hash(perf_hash->TABLE_SIZE);
  }
  object* new;
  new = new_object();
  if(new == NULL)
    return FAIL;
  object_cpy(new,obj);
  if(perf_hash->hashs[hash_index]->objs[obj_index] == NULL){
    perf_hash->hashs[hash_index]->objs[obj_index] = new;
    return SUCCESS;
  }
  return FAIL;
}


int search_perfect_hash(perfect_hash* perf_hash,char label,const object** obj){

  if(perf_hash == NULL)
    return FAIL;
  int hash_index = hash_division(label,perf_hash->TABLE_SIZE),
    obj_index = key_division(label,perf_hash->TABLE_SIZE);

  
  if(perf_hash->hashs == NULL ||
     perf_hash->hashs[hash_index] == NULL ||
     perf_hash->hashs[hash_index]->objs == NULL ||
     perf_hash->hashs[hash_index]->objs[obj_index] == NULL)
    return FAIL;

  
  *obj= perf_hash->hashs[hash_index]->objs[obj_index];
  return SUCCESS;
}
