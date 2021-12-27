#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "object.h"
#include "io.h"
#include "parking.h"
#include "maneuvers.h"
#include "collission.h"
#include "time.h"

int main(int argc, char* argv[]){
  struct rusage *resources= malloc(sizeof(struct rusage)); // structure to account for the time

  // auxiliar struct to get algorithm information
  algorithm_time* algo_time= new_algorithm_time();
  // initialize collission map
  map coll_map = init_map();
  // Files with parking initial config and maneuvers
  FILE* fpc = NULL,*fm=NULL;
  // Process entry
  entry_read(argc,argv,&fpc,&fm);
  int fpc_lines = file_lines(fpc);
  // objects list
  hash* objs = new_hash(fpc_lines);
  // Start to count time
  time_count(resources,START,algo_time);
  // If initialized correctly continue to maneuvers
  if(parking_init(fpc,objs,coll_map)){
    if(DEBUG) print_collission_map(coll_map);
    if(!apply_maneuvers(fm,objs,coll_map)){
      error("Failed in maneuvers apply.");
    }
    time_count(resources,STOP,algo_time);
    // Stop counting the time
    print_algorithm_time(algo_time,stdout);
  }
  else
    error("Error in config file.");
  // dealloc memory
  free_algorithm_time(algo_time);
  free(resources);
  free_hash(objs);
  free_map(coll_map);
  fclose(fpc);
  fclose(fm);
}
