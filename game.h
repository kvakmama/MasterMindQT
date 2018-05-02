/*
 * game.h
 *
 *  Created on: Mar 11, 2018
 *      Author: kvakmama
 */

#ifndef GAME_H_
#define GAME_H_

class game{
    int mat[10][10] = {{0,0,0},{0,0,0},{0,0,0}};
	int next_player = 1;
public:
	void init();
	struct input{
		int row;
		int col;
	};
	input read_input();
	int find_winner();
	bool process_input(input inp);
	bool game_over();
    int get_elem(input inp);
};



#endif /* GAME_H_ */
