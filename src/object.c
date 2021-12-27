#include "object.h"
#include <stdlib.h>
#include <stdio.h>
/* 
COORD_DIF:
   coordinate system origin constant factor difference 
   high level use origin as x=ANY y=ANY and inside program use x=0 y=0 as origin
*/
#define COORD_DIF 1
struct object{
  char label,dir;
  int x,y,size;
};

object* new_object(void){
  object* obj = malloc(sizeof(object));
  if(obj == NULL)
    return NULL;
  return obj;
}

void object_set_all(object* obj,char label,int size,char dir, int x,int y){
  obj->label= label;
  obj->size = size;
  obj->dir = dir;
  obj->x = x;
  obj->y = y;
}
// create object setting variables
object* new_object_s(char label,int size,char dir, int x,int y){
  object* obj = new_object();
  object_set_all(obj,label,size,dir,x,y);
  return obj;
}

void free_object(object* obj){
  if(obj == NULL)
    return;
  free(obj);
}

// Copy a object to another
void object_cpy(object* dest,const object* src){
  if(dest == NULL || src == NULL)
    return;
  *dest= *src;
}

// get the variable label from a object
char obj_get_label(const object *obj){
  return obj->label;
}
char obj_get_dir(const object *obj){
  return obj->dir;
}
int obj_get_size(const object *obj){
  return obj->size;
}
int obj_get_x(const object *obj){
  return obj->x;
}
int obj_get_y(const object *obj){
  return obj->y;
}
void obj_move(object *obj,char dir,int amplitude){
  if(dir == X){
    obj->x+=amplitude;
  }else if(dir == Y){
    obj->y+=amplitude;
  }
}

// normalize coordinates
int normalize_coordinate(int coord){
  return coord-COORD_DIF;
}
int normalize_coordinate_out(int coord){
  return coord+COORD_DIF;
}

