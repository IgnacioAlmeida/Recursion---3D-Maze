#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>
#include "PathfinderInterface.h"
using namespace std;

const int ROW_SIZE = 5;
const int COL_SIZE = 5;
const int FLOOR_SIZE = 5;
const int BACKGROUND = 1;
const int PATH = 3;
const int TEMPORARY = 2;

class Pathfinder : public PathfinderInterface {
public:
	Pathfinder();
	// ~Pathfinder() {};

	string toString() const;

	void createRandomMaze();

	bool importMaze(string file_name);

	vector<string> solveMaze();
	
protected:
  bool find_maze_path(int grid[ROW_SIZE][COL_SIZE][FLOOR_SIZE], int col, int row, int floor);
  vector<string> solution;
	int maze_grid[ROW_SIZE][COL_SIZE][FLOOR_SIZE]; // Holds values
};