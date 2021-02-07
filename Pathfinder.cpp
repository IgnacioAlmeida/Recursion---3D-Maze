#include "Pathfinder.h"

string Pathfinder::toString() const {
	cout << "In toString" << endl;

	stringstream ss;
	for (int row = 0; row < ROW_SIZE; row++){
		for (int col = 0; col < COL_SIZE; col++){
			for (int floor = 0; floor < FLOOR_SIZE; floor++){
				ss << maze_grid[row][col][floor];
			}
		}
		ss << endl;
	}

	return ss.str();
}

bool Pathfinder::importMaze(string file_name){
		cout << "importMaze from " << file_name << endl;
		ifstream file (file_name.c_str());
		if(file.is_open()){
			string line;
			int row_count = 0;
			for (int row = 0; row < ROW_SIZE; row++){
				getline(file,line);
				stringstream ss(line);
				for (int col = 0; col < COL_SIZE; col++){
					int value;
					ss >> value;
					
				}
			}
		}

	}