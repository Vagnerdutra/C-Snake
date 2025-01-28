#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#include "include.h"

int score = 0;

int flag = 1; // stores game state 1:running; 2:game ended; 3:game_paused or menu
World world1 = {1, 1, NULL, NULL, {1, 1}}; // struct that stores the game important variables

int main(int argv, char **argc) {
	alocate_memory(&world1); // dynamic allocates memory for the snake's body and food's positions
	
	int input = start_menu();
	if ( input != 1) {
		flag = 0;
	}
	
	system("cls");
	
	while (flag) {
		print_world(&world1); // print the game
		check_snake(&world1); // check world limit
		check_keyboard_inputs(&world1); 
		
		Sleep(fabs(200 - (11 * score))); // wait a bit, then the snake walks normally
	}
	
	free_memory(&world1); // free the allocated memory
	system("pause");
	return 0;
}