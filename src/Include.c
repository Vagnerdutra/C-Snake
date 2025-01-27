#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "include.h"

int snake_dir_x = 1; // snakes x direction 1: right; -1: left
int snake_dir_y = 0; // snakes y direction 1: up; -1: down
 
void debug(clock_t start, clock_t end) {
	int secs = (end - start);
	printf("Using C%4d", __STDC_VERSION__);
	printf("\nUsed %fs.\n", (float) secs / CLOCKS_PER_SEC);
}


void print_world(World* self) {
	int col = 20, rows = 40;

	printf("\n\n"); 
	for (int i = 0; i < rows + 2; i++) { // print first "#" row
		printf("#");
	}
	printf("\n");
	
	for (int i = 0; i < col; i++) { // print the columns
		printf("#");
		for (int j = 0; j < rows; j++) {
			if (self->snake_body[0][0] == i && self->snake_body[0][1] == j) {
				printf("\033[48;5;240m" " " "\033[0m");
			}
			else {
				printf(" ");
			}
		}
		printf("#\n");
	}
	
	for (int i = 0; i < rows +2; i++) { // print second "#" row
		printf("#");
	}
		
	self->snake_body[0][0] += snake_dir_y;
	self->snake_body[0][1] += snake_dir_x;
		
	printf(BAK); // return cursor to the start, so the next world printed rewrites the last one
}


int alocate_memory(World* self) {
	// try to allocates memory to snake
	self->snake_body = malloc(self->snake_size * sizeof(int)); // try to allocate memory to the snake_corpse (body_square: [x, y])
	if (self->snake_body == NULL) {
		printf("\n Error in alocating memory for snake. \n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < self->snake_size; i++) { // allocate the memory
		self->snake_body[i] = malloc(2 * sizeof(int));
		if (self->snake_body[i] == NULL) {
			printf("\n Error in memory alocating.");
			exit(EXIT_FAILURE);
		}
	}
	self->snake_body[0][0] = self->head_pos[0]; // set snake's x at 5
	self->snake_body[0][1] = self->head_pos[1]; // set snake's y at 5
	
	// try to allocates memory to foods
	self->foods = malloc(self->foods_count * sizeof(int)); // try to allocate the memory to the foods (food: [x, y])
	if (self->foods == NULL) {
		printf("\n Error in alocate memory for foods.");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < self->foods_count; i++) { // allocate the memory
		self->foods[i] = malloc(2 * sizeof(int));
		if (self->foods[i] == NULL) {
			printf("\n Error in memory alocating.");
			exit(EXIT_FAILURE);
		}
	}
	
	return 1;
}


void free_memory(World* self) {
	for (int i = 0; i < self->snake_size; i++) { // frees snake's memory
		free(self->snake_body[i]);
	}
	
	for (int i = 0; i < self->foods_count; i++) { // frees food's memory
		free(self->foods[i]);
	}
}


void check_keyboard_inputs(World* self) {
	if (kbhit()) {
		char input = getch();
		
		if (input == 'w' || input == 'W') {
			snake_dir_y = -1;
			snake_dir_x = 0;
		} else if (input == 's' || input == 'S') {
			snake_dir_y = 1;
			snake_dir_x = 0;
		} else if (input == 'a' || input == 'A') {
			snake_dir_x = -1;
			snake_dir_y = 0;
		} else if (input == 'd' || input == 'D') {
			snake_dir_x = 1;
			snake_dir_y = 0;
		}
	}
}