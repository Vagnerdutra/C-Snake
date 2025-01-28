#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#include "include.h"

#define COL 20
#define ROWS 40

extern int score;

int snake_dir_x = 1; // snakes x direction 1: right; -1: left
int snake_dir_y = 0; // snakes y direction 1: up; -1: down
 
void debug(clock_t start, clock_t end) {
	int secs = (end - start);
	printf("Using C%4d", __STDC_VERSION__);
	printf("\nUsed %fs.\n", (float) secs / CLOCKS_PER_SEC);
}


void print_world(World* self) {
	printf("\n"); 
	for (int i = 0; i < ROWS + 2; i++) { // print first "#" row
		printf("#");
	}
	printf("\n");
	
	for (int i = 0; i < COL; i++) { // print the columns
		printf("#");
		for (int j = 0; j < ROWS; j++) {
			if (self->snake_body[0][0] == i && self->snake_body[0][1] == j) {
				printf("\033[48;5;240m" " " "\033[0m");
			} else if (self->foods[0][0] == i && self->foods[0][1] == j) {
				printf("o"); 
			} else {
				printf(" ");
			}
		}
		printf("#\n");
	}
	
	for (int i = 0; i < ROWS +2; i++) { // print second "#" row
		printf("#");
	}
		
	self->snake_body[0][0] += snake_dir_y;
	self->snake_body[0][1] += snake_dir_x;
		
	printf("\n\n\tScore: %d", score); // return cursor to the start, so the next world printed rewrites the last one
	printf(BAK);
}


int alocate_memory(World* self) {
	srand(time(NULL)); // feed srand for the food's random position
	
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
	self->foods[0][0] = 1 + rand() % (COL - 1);
	self->foods[0][1] = 1 + rand() % (ROWS - 1);
	
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
	if (kbhit()) { // check if a button is pressed
		char input = getch(); // get the pressed button
		
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


int start_menu() {
	system("cls"); // clear everything, for the case that the program has executed in prompt
	printf("\n\n~~~~~~~~~~~~~ C-SNAKE ~~~~~~~~~~~~~\n\n"); // print the menu
	printf("Insert 1 to start the game.\nInsert anything else to end the program.\n");
	printf("\n~~~~~~~~~~~~~ C-SNAKE ~~~~~~~~~~~~~\n?: ");
	
	int input;
	scanf("%d", &input); // get the input
	if (input == 1) {
		return 1;
	}
	return 0;
}


int lose_menu() {
	system("cls");
	printf("\n~~~~~~~~~~~~~ C-SNAKE ~~~~~~~~~~~~~\n\n");
	printf("\nYou losed! Insert 1 to restart or somethyng else to end.\n");
	printf("\n\n~~~~~~~~~~~~~ C-SNAKE ~~~~~~~~~~~~~\n?: ");
	
	int input;
	scanf("%d", &input);
	if (input == 1) {
		return 1;
	}
	return 0;
}

void check_snake(World* self) {
	if (self->snake_body[0][1] < 0 || self->snake_body[0][1] >= ROWS || self->snake_body[0][0] < 0 
	|| self->snake_body[0][0] >= COL) { // verify the x borders
		lose_menu();
		restart_world(self);
		system("cls");
	} else if (self->snake_body[0][1] == self->foods[0][1] && self->snake_body[0][0] == self->foods[0][0]) {
		score++;
		self->foods[0][0] = 1 + rand() % (COL - 1);
		self->foods[0][1] = 1 + rand() % (ROWS - 1);
	}
}

void restart_world(World* self) {
	free_memory(self);
	
	self->snake_size = 1;
	self->foods_count = 0;
	self->snake_body = NULL;
	self->foods = NULL;
	self->head_pos[0] = 1;
	self->head_pos[1] = 1;
	
	alocate_memory(self);
}