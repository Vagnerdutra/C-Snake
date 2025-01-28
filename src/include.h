#ifndef _SOURCES_
#define _SOURCES_

#define BAK "\033[H"

typedef struct { // stores game's important variables
	int snake_size;
	int foods_count;
	int** snake_body;
	int** foods;
	int head_pos[2];
}World;

int alocate_memory(World* self); // allocate memory to the game actors (snake and foods)
int start_menu(); // print start menu and get the input
int lose_menu(); // print lose menu
void restart_world(World* self); 
void check_snake(World* self); // check world bord 
void free_memory(World* self); // frees the allocated memory
void debug(clock_t start, clock_t end); // given the start time and end, print the used time and the C version
void print_world(World* self);
void check_keyboard_inputs(World* self);

#endif