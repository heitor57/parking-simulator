#include "parking.h"
#include "io.h"
#include "object.h"
#include <stdlib.h>


int parking_init(FILE* fpc,hash* objs,map coll_map){
  char label,dir;
  int x,y,size;
  object* obj=new_object();
  while(!feof(fpc)){
    fscanf(fpc,"%c %d %c %*c%d%*c%d\n",&label,&size,&dir,&x,&y);

    object_set_all(obj,label,
		       size,
		       dir,
		       normalize_coordinate(x),
		       normalize_coordinate(y));
    if(!insert_hash(objs,obj)){
      error("Error adding the object to the list of objects.");
      obj_print(obj);
      free_object(obj);
      return FAIL;
    }
    if(!collission_map_insert(coll_map,obj)){
      error("Collission happened in parking configuration file. Objects in same position.");
      free_object(obj);
      return FAIL;
    }
  }
  free_object(obj);
  return SUCCESS;
}


int parking_init_perfect(FILE* fpc,perfect_hash* objs,map coll_map){
  char label,dir;
  int x,y,size;
  object* obj=new_object();
  while(!feof(fpc)){
    fscanf(fpc,"%c %d %c %*c%d%*c%d\n",&label,&size,&dir,&x,&y);

    object_set_all(obj,label,
		       size,
		       dir,
		       normalize_coordinate(x),
		       normalize_coordinate(y));
    if(!insert_perfect_hash(objs,obj)){
      error("Error adding the object to the list of objects.");
      obj_print(obj);
      free_object(obj);
      return FAIL;
    }
    if(!collission_map_insert(coll_map,obj)){
      error("Collission happened in parking configuration file. Objects in same position.");
      free_object(obj);
      return FAIL;
    }
  }
  free_object(obj);
  return SUCCESS;
}

