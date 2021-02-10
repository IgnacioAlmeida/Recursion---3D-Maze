#include "Pathfinder.h"


Pathfinder::Pathfinder(){
	cout << "In constructor" << endl;
	for (int row = 0; row < ROW_SIZE; row++){
		for (int col = 0; col < COL_SIZE; col++){
			for (int floor = 0; floor < FLOOR_SIZE; floor++){
				maze_grid[row][col][floor] = 1;
			}
		}
	}
}
string Pathfinder::toString() const {
	cout << "In toString" << endl;
	stringstream ss;
	for (int row = 0; row < ROW_SIZE; row++){
		for (int col = 0; col < COL_SIZE; col++){
		  ss << endl;
			for (int floor = 0; floor < FLOOR_SIZE; floor++){
				ss << maze_grid[row][col][floor] << " ";
			}
		}
		ss << endl;
	}

	return ss.str();
}

void Pathfinder::createRandomMaze(){
	cout << "Creating random maze" << endl;

	for (int row = 0; row < ROW_SIZE; row++){
		for (int col = 0; col < COL_SIZE; col++){
			cout << endl;
			for (int floor = 0; floor < FLOOR_SIZE; floor++){
				maze_grid[row][col][floor] = rand() % 2;
				cout << maze_grid[row][col][floor] << " ";
			}
		}
		cout << endl;
	}
	maze_grid[0][0][0] = 1;
	maze_grid[4][4][4] = 1;
}

bool Pathfinder::importMaze(string file_name){
	cout << "importMaze from "<<file_name<<endl;
	ifstream file (file_name.c_str());
	if (file.is_open()) {
		string line;
		for (int floor = 0; floor < FLOOR_SIZE; floor++){		
			for (int row = 0; row < ROW_SIZE; row++){
				getline(file, line);
				stringstream ss(line);
				for (int col = 0; col < COL_SIZE; col++){
					int value;
					ss >> value;
					// cout << value << " ";
					maze_grid[row][col][floor] = value;
				}
				cout << endl;
			}
		cout << endl;
		getline(file, line); //FIXME We don't want to get the last line
		}
	}
	return true;
}

bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][FLOOR_SIZE],int col, int row, int floor) {
	cout << "In find_maze_path" << endl;
	solution.push_back("(" + to_string(col) + "," + to_string(row) + "," + to_string(floor) + ")");
	cout << "find_maze_path [" << col << "][" << row << "][" << floor << "]" << endl;
	//Base cases
	if (col < 0 || row < 0 || floor < 0 || col >= COL_SIZE || row >= ROW_SIZE || floor >= FLOOR_SIZE)
		return false; //If it is out of bound
	else if (grid[col][row][floor] != BACKGROUND)
		return false; //If we've been there before
	else if (col == COL_SIZE - 1 && row == ROW_SIZE - 1 && floor == FLOOR_SIZE){
		grid[col][row][floor] = PATH;
		solution.push_back("(" + to_string(col) + ", " + to_string(row) + ", " + to_string(floor) + ")");
		return true;
	}
	else {
		//Recursive case.
		//Attempt to find a path from each neighbor while marking the cell with a 3 as on path.
		grid[col][row][floor] = PATH;
		if (find_maze_path(grid, col - 1, row, floor)
			|| find_maze_path(grid, col + 1, row, floor)
			|| find_maze_path(grid, col, row - 1, floor)
			|| find_maze_path(grid, col, row + 1, floor)
			|| find_maze_path(grid, col, row, floor + 1)
			|| find_maze_path(grid, col, row, floor - 1)) {
			solution.push_back("(" + to_string(col) + ", " + to_string(row) + ", " + to_string(floor) + ")");
			return true;
		}
		else
			grid[col][row][floor] = TEMPORARY;
			return false;

	}
}

vector<string> Pathfinder::solveMaze(){
	cout << "in solveMaze" << endl;
	find_maze_path(maze_grid,0,0,0);
	for (auto s:solution){
			cout << s << endl;
	}
	return solution;
}