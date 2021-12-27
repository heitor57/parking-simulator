#include "maneuvers.h"
#include "object.h"
#include "io.h"
#include <math.h>
extern bool DEBUG;
// Variables defining the objective(XY) to reach of the object
// 6 - 1 and 4 - 1
#define X_END 5
#define Y_END 3
#define MAIN_OBJ 'Z'

// min maneuvers file size
#define MIN_FM_SIZE 3
// check if file has maneuvers
int check_have_maneuvers(FILE* fm){
  fseek(fm,0,SEEK_END);
  if(ftell(fm) < MIN_FM_SIZE)
    return FAIL;
  rewind(fm);
  return SUCCESS;
}

int apply_maneuvers(FILE* fm,hash* objs,map coll_map){
  if(check_have_maneuvers(fm)){
    char label,dir;
    int amplitude;
    object* obj;
    obj = NULL;
    while(!feof(fm)){
      // Get the maneuver from the file
      fscanf(fm,"%c %c %d\n",&label,&dir,&amplitude);
      // Find the object to move
      if(DEBUG) printf("%c %c %d\n",label,dir,amplitude);
      // search for the object
      if(!search_hash(objs,label,(const object**)&obj)){
	error("Label %c not found",label);
	return FAIL;
      }
      int sense= amplitude/fabs(amplitude);
      amplitude = fabs(amplitude);
      // move object, removing from collission map and inserting, simulating movement
      for(int i = 0; i<amplitude; i++){
	collission_map_remove(coll_map,obj);
	obj_move(obj,dir,sense);
	if(!collission_map_insert(coll_map,obj)){
	  error("Collission happened");
	  return FAIL;
	}
	if(DEBUG) print_collission_map(coll_map);
      }
    }
  }
  // Check if reached the final
  if(coll_map[Y_END][X_END] == MAIN_OBJ)
    printf("%c Reached the end! Y %d X %d\n",
	   MAIN_OBJ,
	   normalize_coordinate_out(Y_END),
	   normalize_coordinate_out(X_END));
  else
    printf("%c Did not reach the end! Y %d X %d\n",
	   MAIN_OBJ,
	   normalize_coordinate_out(Y_END),
	   normalize_coordinate_out(X_END));

  return SUCCESS;
}
int apply_maneuvers_perfect(FILE* fm,perfect_hash* objs,map coll_map){
  if(check_have_maneuvers(fm)){
    char label,dir;
    int amplitude;
    object* obj;
    obj = NULL;
    while(!feof(fm)){
      // Get the maneuver from the file
      fscanf(fm,"%c %c %d\n",&label,&dir,&amplitude);
      // Find the object to move
      if(DEBUG) printf("%c %c %d\n",label,dir,amplitude);
      if(!search_perfect_hash(objs,label,(const object**)&obj)){
	error("Label %c not found",label);
	return FAIL;
      }
      int sense= amplitude/fabs(amplitude);
      amplitude = fabs(amplitude);
      for(int i = 0; i<amplitude; i++){
	collission_map_remove(coll_map,obj);
	obj_move(obj,dir,sense);
	if(!collission_map_insert(coll_map,obj)){
	  error("Collission happened");
	  return FAIL;
	}
	if(DEBUG) print_collission_map(coll_map);
      }
    }
  }
  // Check if reached the final
  if(coll_map[Y_END][X_END] == MAIN_OBJ)
    printf("%c Reached the end! Y %d X %d\n",
	   MAIN_OBJ,
	   normalize_coordinate_out(Y_END),
	   normalize_coordinate_out(X_END));
  else
    printf("%c Did not reach the end! Y %d X %d\n",
	   MAIN_OBJ,
	   normalize_coordinate_out(Y_END),
	   normalize_coordinate_out(X_END));

  return SUCCESS;
}
