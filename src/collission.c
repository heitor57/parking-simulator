#include "collission.h"
#include "parking.h"
#include "io.h"
#include <stdlib.h>
void clean_map(map map){
  int i,j;
  for(i=0; i<MAP_SIZE;i++)
    for(j=0; j<MAP_SIZE;j++)
      map[i][j] = Empty;
}
map init_map(void){
  map map = malloc(MAP_SIZE*sizeof(point*));
  for(int i=0; i<MAP_SIZE;i++){
    map[i] = malloc(MAP_SIZE*sizeof(point));
  }
  clean_map(map);
  return map;
}
void free_map(map coll_map){
  for(int i=0; i<MAP_SIZE;i++)
    free(coll_map[i]);
  free(coll_map);
}
// insert collission points on the map
int dir_to_int(char *dir){
  return *dir-X;
}

int collission_map_insert(map coll_map,object* obj){
  int size = obj_get_size(obj);
  // decrement 1 to normalize for vector
  int x = obj_get_x(obj),y = obj_get_y(obj);
  char dir = obj_get_dir(obj),label = obj_get_label(obj);
  bool dir_is_x = (dir == X) ? true : false,
    dir_is_y = (dir == Y) ? true : false; 
  // check if the coordinates are inside the map
  if(x<0 || y<0){
    error("Position out of the map.");
    return FAIL;
  }
  for(int i = 0; i<size;i++,x+=dir_is_x,y+=dir_is_y)
      if(x<MAP_SIZE && y<MAP_SIZE)
	if(coll_map[y][x] == Empty)
	  coll_map[y][x] = label;
	else
	  return FAIL;
      else
	return FAIL;
  return SUCCESS;
}

int collission_map_remove(map coll_map,object* obj){
// decrement 1 to normalize for vector
  int size = obj_get_size(obj),
    x = obj_get_x(obj),
    y = obj_get_y(obj);
  char dir = obj_get_dir(obj);
  bool dir_is_x = (dir == X) ? true : false,
    dir_is_y = (dir == Y) ? true : false; 

// check if the coordinates are inside the map
  if(x<0 || y<0){
    error("Position out of the map.");
    return FAIL;
  }
  for(int i = 0; i<size; i++,x+=dir_is_x,y+=dir_is_y)
    if(x<MAP_SIZE && y<MAP_SIZE)
      if(coll_map[y][x] != Empty)
	coll_map[y][x] = Empty;
      else
	printf("Point already empty.");
    else{
      error("Position out of the map.");
      return FAIL;
    }
  return SUCCESS;
}

// Map insert but clear FAIL insert, in other words, dont spoil the map
int collission_map_insert_persistent(map coll_map,object* obj){
  int size = obj_get_size(obj);
  // decrement 1 to normalize for vector
  int x = obj_get_x(obj),y = obj_get_y(obj);
  char dir = obj_get_dir(obj),label = obj_get_label(obj);
  bool dir_is_x = (dir == X) ? true : false,
    dir_is_y = (dir == Y) ? true : false; 

  if(x<0 || y<0){
    error("Position out of the map.");
    return FAIL;
  }

  for(int i = 0; i<size;i++,x+=dir_is_x,y+=dir_is_y)
    if(x<MAP_SIZE && y<MAP_SIZE)
      if(coll_map[y][x] == Empty)
	coll_map[y][x] = label;
      else
      {
	// Clearing the inserts maded
	for(int j=1; j<=i;j++)
	  coll_map[y-j*dir_is_y][x-j*dir_is_x] = Empty;
	return FAIL;
      }
    else{
      for(int j=1; j<=i;j++)
	coll_map[y-j*dir_is_y][x-j*dir_is_x] = Empty;
      return FAIL;
    }

  return SUCCESS;
}
