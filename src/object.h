#ifndef OBJECT_H
#define OBJECT_H
#define X 'X'
#define Y 'Y'

typedef struct object object;
object* new_object(void);
void object_set_all(object* obj,char label,int size,char dir, int x,int y);
object* new_object_s(char label,int size,char dir, int x,int y);
void free_object(struct object* obj);
void object_cpy(object* dest,const object* src);
// access functions
char obj_get_label(const object *obj);
char obj_get_dir(const object *obj);
int obj_get_size(const object *obj);
int obj_get_x(const object *obj);
int obj_get_y(const object *obj);
void obj_move(object *obj,char dir,int amplitude);
int normalize_coordinate(int coord);
int normalize_coordinate_out(int coord);

#endif
