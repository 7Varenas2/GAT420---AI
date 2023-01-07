#include <iostream>
#include <vector>
#include <array>

using namespace std;

/*
* 1/5/23 Cellular Automaton - Recreates a cellular automaton by using 4 rules - 30, 90 ,110, 184 - and a random seed rule using the time function.
*/

void DisplayCellsRow(const vector<bool>& cells)
{
	// Display a row of cells to the console
	// Display a 'X' if the cell is alive (true) or a '-' if dead (false)
	// Place a space between characters
	// Example: - - XX - - X - - - X - -
	for (auto cell : cells)
	{
		if (cell)
		{
			cout << "X" << " ";
		}
		else
		{
			cout << "-" << " ";
		}

	}
	// Go to the next line after the displaying the row
	cout << "\n";
}

vector<bool> ProcessCells(const vector<bool>& cells, const array<bool, 8>& rule)
{
	// Create cells that willstore the cell states after being processed
	// Use constructor that takes the number of elements to create
	vector<bool> processed(cells);

	for (int i = 0; i < processed.size(); i++)
	{
		// Get the current and neighboring cell states using (i) index 
		int left = i - 1;
		int center = i;
		int right = i + 1;

		// Wrap left and right index if past the edges (left < 0 or right >= size) Just like in Graphics, it is the coordinates/grid
		// left = (i - 1) < 0 -> size - 1
		// right = i + 1 == size -> 0
		if (left < 0)
		{
			left = processed.size() - 1;
		}
		else if (right >= processed.size())
		{
			right = 0;
		}
		bool states[3];
		states[0] = cells[left];
		states[1] = cells[center];
		states[2] = cells[right];



		bool state = false;
		
		// Current pattern 111 110 101 100 011 010 001 000
		// rule             0   1   2   3   4   5   6   7

		// 111
		if (states[0] && states[1] && states[2]) state = rule[0];
		// 110
		else if (states[0] && states[1] && !states[2]) state = rule[1];
		// 101
		else if (states[0] && !states[1] && states[2]) state = rule[2];
		// 100
		else if (states[0] && !states[1] && !states[2]) state = rule[3];
		// 011
		else if (!states[0] && states[1] && states[2]) state = rule[4];
		// 010
		else if (!states[0] && states[1] && !states[2]) state = rule[5];
		// 001
		else if (!states[0] && !states[1] && states[2]) state = rule[6];
		// 000
		else if (!states[0] && !states[1] && !states[2]) state = rule[7];

		// Set processed at index (i) to state
		processed[i] = state;
	}
	return processed;
}

int main()
{
	// Declare a variable for the number of cells in a row (50)
	int cellRows = 50;
	// Declare a variable for the number of iterations (40)
	int iter = 40;

	// Create a vector of cell states boolean (true = alive/false = dead)
	// there is a constructor taht allows you to provide the number of elements and the default value (int, bool)
	vector<bool> cells(cellRows, false);
	cells[cellRows / 2] = true;
	//srand((unsigned int)time(nullptr));
	//
	//for (int i = 0; i < 5; i++)
	//{
	//	cells[rand() % cellRows - 1] = true;
	//}

	// Set the text to a different color (Uses hex 0 - A)
	// First valye is background and second foreground
	system("Color 0D");

	// Rules
	array<bool, 8> rule30 = { 0,0,0,1,1,1,1,0 };
	array<bool, 8> rule90 = { 0,1,0,1,1,0,1,0 };
	array<bool, 8> rule110 = { 0,1,1,0,1,1,1,0 };
	array<bool, 8> rule184 = { 1,0,1,1,1,0,0,0 };


	// Display Iteration
	for (int i = 0; i < iter; i++)
	{
		DisplayCellsRow(cells);
		cells = ProcessCells(cells, rule184);
	}

}

