/*
 * game.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: kvakmama
 */

#include "game.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int row,col = 0;

void game::init(){
	next_player = 1;
	cout << "initial\n";
	for ( int i = 0; i < 3; i++ ) {
		for ( int j = 0; j < 3; j++ ) {
			mat[i][j] = 0;
			cout << mat[i][j] << " ";
			}
		cout << endl;
		}

}
int game::find_winner(){
	if(
				((mat[0][0]!=1) || (mat[1][1]!=1) || (mat[2][2]!=1))&&
				((mat[0][0]!=2) || (mat[1][1]!=2) || (mat[2][2]!=2))&&
				//r2l
				((mat[0][2]!=1) || (mat[1][1]!=1) || (mat[2][0]!=1))&&
				((mat[0][2]!=2) || (mat[1][1]!=2) || (mat[2][0]!=2))&&
				//1row
				((mat[0][0]!=1) || (mat[0][1]!=1) || (mat[0][2]!=1))&&
				((mat[0][0]!=2) || (mat[0][1]!=2) || (mat[0][2]!=2))&&
				//2row
				((mat[1][0]!=1) || (mat[1][1]!=1) || (mat[1][2]!=1))&&
				((mat[1][0]!=2) || (mat[1][1]!=2) || (mat[1][2]!=2))&&
				//3row
				((mat[2][0]!=2) || (mat[2][1]!=2) || (mat[2][2]!=2))&&
				((mat[2][0]!=2) || (mat[2][1]!=2) || (mat[2][2]!=2))&&
				//lcol
				((mat[0][0]!=1) || (mat[1][0]!=1) || (mat[2][0]!=1))&&
				((mat[0][0]!=2) || (mat[1][0]!=2) || (mat[2][0]!=2))&&
				//2col
				((mat[0][1]!=1) || (mat[1][1]!=1) || (mat[2][1]!=1))&&
				((mat[0][1]!=2) || (mat[1][1]!=2) || (mat[2][1]!=2))&&
				//3col
				((mat[0][2]!=1) || (mat[1][2]!=1) || (mat[2][2]!=1))&&
				((mat[0][2]!=2) || (mat[1][2]!=2) || (mat[2][2]!=2))
		)
	{
		return 0;
	}
	return 3-next_player;
}

bool game::game_over(){
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			if (mat[i][j] == 0)
			{
				int winner = find_winner();
				if (winner == 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

int y = 0;
int kaki(){
	bool valid = false;
	while (!valid)
			{
				valid = true;
				cout <<"Please enter an Integer"<< endl;
				cin >> y;
				if(cin.fail() || (y>2) || (y<0) )
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					cout << "Please enter an Integer between 0-2." << endl;
					valid = false;
				}
			}
	return y;
}

int kaki2(string goal)
{
	int y;
	do {
		cin.clear();
		cin.ignore();
		cout << "Please enter an integer for " << goal << "\n";
		cin >> y;
	} while(cin.fail() || y < 0 || y > 2);
	return y;
}

int game::get_elem(input inp)
{
    return mat[inp.row][inp.col];
}

game::input game::read_input(){

	row = kaki();
	col = kaki();
	return input{row,col};
}

bool game::process_input(input inp){
	cout << "process\n";
	if (mat[inp.row][inp.col] != 0)
	{
		return false;
	}
	mat[inp.row][inp.col] = next_player;

	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	next_player = 3-next_player;
	return true;
}
