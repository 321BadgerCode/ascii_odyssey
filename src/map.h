#pragma once

#include <iostream>
#include <string>
#include "./clr.h"
#include "./vector.h"

using namespace std;

class map{
public:
	string name;
	char* grid;
	ao::vector<int> size;
	ao::vector<int> player_pos;

	map(const string& mapName, char* mapGrid, ao::vector<int> size, const ao::vector<int>& player_pos2):name(mapName),grid(mapGrid),size(size),player_pos(player_pos2){}
	map(const string& filename){
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Failed to open file: " << filename << endl;
			return;
		}

		string line;
		getline(file, name);
		size=*new ao::vector<int>(0,0);

		//calculate the number of rows and columns in the grid.
		while (getline(file, line)) {
			if (line.empty()) {
				break;
			}
			size.x++;
			size.y = max(size.y, static_cast<int>(line.length()));
		}

		//reset file pointer to the beginning of the grid.
		file.clear();
		file.seekg(file.beg + name.length() + 1);

		//allocate memory for the grid.
		grid = new char[size.x * size.y];

		//read the grid from the file.
		int row = 0;
		while (getline(file, line)) {
			if (line.empty()) {
				break;
			}
			int col = 0;
			for (char c : line) {
				grid[row * size.y + col] = c;
				++col;
			}
			//pad the remaining columns with empty spaces if necessary.
			while (col < size.y) {
				grid[row * size.y + col] = ' ';
				++col;
			}
			++row;
		}

		file.close();

		player_pos=get_player_pos();
	}
	void move_player(const ao::vector<int> pos){
		//calculate the new player position.
		ao::vector<int> newPlayerPos = player_pos + ao::vector<int>(pos.x, pos.y);

		//check if the new position is within the grid boundaries.
		if (newPlayerPos.x >= 0 && newPlayerPos.x < size.x && newPlayerPos.y >= 0 && newPlayerPos.y < size.y) {
			//check if the new position is not a wall ('#').
			if (grid[newPlayerPos.x * size.y + newPlayerPos.y] != '#') {
				//move the player to the new position.
				grid[player_pos.x * size.y + player_pos.y] = ' ';
				grid[newPlayerPos.x * size.y + newPlayerPos.y] = 'o';
				player_pos = newPlayerPos;
			}
		}
	}
	ao::vector<int> get_player_pos() const {
		for (int i = 0; i < size.x; ++i) {
			for (int j = 0; j < size.y; ++j) {
				if (grid[i * size.y + j] == 'o') {
					return ao::vector<int>(i, j);
				}
			}
		}

		//return an invalid position if player not found.
		return ao::vector<int>(-1, -1);
	}
	operator string() const {
		cout << name << endl;

		for (int i = 0; i < size.x; ++i) {
			for (int j = 0; j < size.y; ++j) {
				string c=string(1,grid[i*size.y+j]);
				string c2=	(c=="o")?
						color::set_clr(c,color::blue,color::type::fg):
						c;
				cout<<c2;
			}
			cout << endl;
		}
	}
	~map() {
		delete[] grid;
	}
};
//TODO: npc_pos vector array to put into map in string cast overload.
//	-if player touches npc similar to how it touches boundaries, npc talks w/ player.