#include "Pathfinder.h"

Pathfinder::Pathfinder(){
	for (int floor = 0; floor < FLOOR_SIZE; floor++){
		for (int row = 0; row < ROW_SIZE; row++){
			for (int col = 0; col < COL_SIZE; col++){
				maze_grid[col][row][floor] = 1;
			}
		}
	}
}
string Pathfinder::toString() const {
	stringstream ss;
	for (int floor = 0; floor < FLOOR_SIZE; floor++){
		for (int row = 0; row < ROW_SIZE; row++){
			for (int col = 0; col < COL_SIZE; col++){
				if(col != 4)
					ss << maze_grid[col][row][floor] << " ";
				else
					ss << maze_grid[col][row][floor];
			}
			ss << endl;
		}
		if (floor != 4)
			ss << endl;
	}
	return ss.str();
}

void Pathfinder::createRandomMaze(){
	for (int floor = 0; floor < FLOOR_SIZE; floor++){
		for (int row = 0; row < ROW_SIZE; row++){
			cout << endl;
			for (int col = 0; col < COL_SIZE; col++){
				maze_grid[col][row][floor] = rand() % 2;
				// cout << maze_grid[row][col][floor] << " ";
			}
		}
		cout << endl;
	}
	maze_grid[0][0][0] = 1;
	maze_grid[4][4][4] = 1;
}

bool Pathfinder::importMaze(string file_name){
	cout << "importMaze from "<< file_name << endl;;
	ifstream file (file_name.c_str());
	ifstream checkFile(file_name.c_str());
	if (checkFile.is_open()){
		string checkLine;
		int counter = 0;
		while(checkFile >> checkLine){
			counter++;
		}
		if(counter != 125)
			return false;
	}
	if (file.is_open()) {
		string line;
		// int row_count = 0;
		for (int floor = 0; floor < FLOOR_SIZE; floor++){		
			for (int row = 0; row < ROW_SIZE; row++){
				getline(file, line);
				stringstream ss(line);
				for (int col = 0; col < COL_SIZE; col++){
					int value;
					ss >> value;
					if(ss.fail())
						return false;
					if(value != 0 && value != 1)
						return false;	
					maze_grid[col][row][floor] = value;
				}
				cout << endl;
			}	
		cout << endl;
		getline(file, line);
		}
	}
	if (maze_grid[0][0][0] != 1 || maze_grid[4][4][4] != 1)
		return false;
	return true;
}

bool Pathfinder::find_maze_path(int grid[COL_SIZE][ROW_SIZE][FLOOR_SIZE],int col, int row, int floor) {
	cout << this->toString();
	// solution.push_back("(" + to_string(col) + ", " + to_string(row) + ", " + to_string(floor) + ")");
	//Base cases
	if (col < 0 || row < 0 || floor < 0 || col >= COL_SIZE || row >= ROW_SIZE || floor >= FLOOR_SIZE)
		return false; //If it is out of bound
	else if (grid[col][row][floor] != BACKGROUND)
		return false; //If we've been there before
	else if (col == COL_SIZE - 1 && row == ROW_SIZE - 1 && floor == FLOOR_SIZE - 1){
		grid[col][row][floor] = PATH; //If it's the exit
		solution.push_back("(" + to_string(col) + ", " + to_string(row) + ", " + to_string(floor) + ")");
		return true; 
	}
	else{
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
	solution.clear();
	find_maze_path(maze_grid,0,0,0);
	reverse(solution.begin(), solution.end());
	for (int floor = 0; floor < FLOOR_SIZE; floor++){
		for (int row = 0; row < ROW_SIZE; row++){
			for (int col = 0; col < COL_SIZE; col++){
				if (maze_grid[col][row][floor] != 0)
					maze_grid[col][row][floor] = 1;
			}
		}
	}
	return solution;
}