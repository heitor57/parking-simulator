#include "io.h"
#include <getopt.h>
#include <stdlib.h>
bool DEBUG = false;
void print_usage(){
  printf("Usage: parking-simulator(-perfect) -c <config file> & -m <maneuvers file> & -d (DEBUG)\n");
  exit(ENOENT);
}

void entry_read(int argc, char* argv[],FILE** fpc,FILE** fm){
  int option;
  //int check=0;
  if(argc < 5)
  {
    print_usage();
  }
  while((option = getopt(argc,argv,"c:m:d")) != -1){
    switch(option){
    case 'c':
      if(!(*fpc = fopen(optarg,"r"))){
	error("Initial configuration file open error.");
	exit(ENOENT);
      }
      break;
    case 'm':
      if(!(*fm = fopen(optarg,"r"))){
	error("Maneuvers file open error.");
	exit(ENOENT);
      }
      break;

    case 'd':
      DEBUG=true;
      break;
    }
  }
}
int file_lines(FILE* f){
  int i=0;
  while(!feof(f)){
    if(fgetc(f) == '\n')
      i++;
  }
  rewind(f);
  return i;
}

void print_collission_map(map cmap){
  printf("Y+---+---+---+---+---+---+\n");
  for(int i =5;i>=0;i--){
    printf("%d",i+1);
    for(int j = 0;j<6;j++)
      printf("| %c ",cmap[i][j]=='0'? ' ': cmap[i][j]);
    printf("|\n +---+---+---+---+---+---+\n");
  }
  printf("   1   2   3   4   5   6 X\n\n");
}

void obj_print(object* obj){
  printf("\
Object: %c (x,y)(%d,%d)\n\
Direction: %c\n\
Size: %d\n",
	 obj_get_label(obj),
	 normalize_coordinate_out(obj_get_x(obj)),
	 normalize_coordinate_out(obj_get_y(obj)),
	 obj_get_dir(obj),
	 obj_get_size(obj));
}

void print_algorithm_time(const algorithm_time *algo_time,FILE* f){
  fprintf(f,"User time %.6fs, System time %.6fs, Total Time %.6fs\n",get_utime(algo_time), get_stime(algo_time), get_total_time(algo_time));
}
