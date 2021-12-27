#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h> //for truncate
#include <stdbool.h>
#include "collission.h"
#include "object.h"
#include "io.h"
#define TEST_LIMIT 10000000
#define CHARS_NUMBER 26
enum {ASCII_L=65,ASCII_H=90};
int ASCII_RANGE = ASCII_H - ASCII_L,
  TEMP_ASCII_H = 90;
enum {CAR_SIZE = 2, TRUCK_SIZE};
const int objs_size[] = {CAR_SIZE,TRUCK_SIZE},
  n_objs = sizeof(objs_size)/sizeof(int);
bool characters[CHARS_NUMBER];
void print_usage_generator();

int main(int argc,char *argv[]){
  int option,max_n;
  char *file_name;
  FILE* fpc = stdout;

  if(argc == 1)
  {
    print_usage_generator();
    return 0;
  }
  while((option = getopt(argc,argv,"n:o:")) != -1){
    switch(option){
    case 'n':
      if(atoi(optarg)>0)
	max_n = atoi(optarg);
      else{
	print_usage_generator();
	return 1;
      }
      break;
    case 'o':
      file_name = optarg;
      if(!(fpc = fopen(optarg,"w")))
      {
	error("Error in openning the output file of generator.");
	print_usage_generator();
	return ENOENT;
      }
      break;
    }
  }

  if(max_n>MAP_SIZE*MAP_SIZE/CAR_SIZE){
    error("The map does not support this amount of object.");
    return 0;
  }
  int n=0,same_n_test_times=0;
  object *obj = new_object();
  map cmap=init_map();
  int resets = 0;
  int char_index;
reset:
  for(int i=0;i<sizeof(characters);i++)
    characters[i]=false;
  char_index = ASCII_RANGE;
  srand(time(NULL));
  while(max_n > n){
    same_n_test_times++;
    int rand_dir = rand();
    if(characters[char_index]){
      char_index=rand()%CHARS_NUMBER;
      if(characters[char_index]){
	int i;
	for(i = 0 ;i < CHARS_NUMBER && characters[i];i++);
	char_index=i;
      }
    }
    
    object_set_all(obj,char_index+ASCII_L,
		   objs_size[rand()%n_objs],
		   X*(rand_dir%2)+Y*((rand_dir+1)%2),
		   rand()%MAP_SIZE,
		   rand()%MAP_SIZE);
    if(collission_map_insert_persistent(cmap,obj)==SUCCESS){
      fprintf(fpc,"%c %d %c X%dY%d\n",
	      obj_get_label(obj),
	      obj_get_size(obj),
	      obj_get_dir(obj),
	      normalize_coordinate_out(obj_get_x(obj)),
	      normalize_coordinate_out(obj_get_y(obj)));
      characters[char_index]= true;
      n++;
      same_n_test_times = 0;
    }else if(same_n_test_times>=TEST_LIMIT){
      printf("Reset: %d\n",++resets);
      
      n=0;
      same_n_test_times = 0;

      clean_map(cmap);
      if(file_name!=NULL)
      {
	freopen(file_name,"w",fpc);
      }
      goto reset;
    }
  }
  print_collission_map(cmap);
  free_object(obj);
  free_map(cmap);
  fclose(fpc);
}

void print_usage_generator(){
  printf("Usage: generator -n <number of objects> & -o <output file>\n");
  exit(ENOENT);
}
