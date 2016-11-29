#include <iostream>
#include "types/point.h"
#include "types/block.h"
#include "types/grid.h"
#include "constants/constants.h"

int main(void)
{	
	system("clear\n");
	cout << "Sudoku Solver v1.0" << endl << endl;
	
	Grid grid(11);	
	//grid.loadStartingValues();	
	grid.getStartingValues();	
	grid.printGrid("Unsolved Sudoku");
	
	while(!grid.isComplete)
	{
		while(grid.newPercentage != grid.oldPercentage)
		{
			grid.oldPercentage = grid.getPercentageComplete();
			grid.pointCheck();	
			grid.blockCheck();
			grid.newPercentage = grid.getPercentageComplete();
		}		
		
		if 	(!grid.isComplete)
		{
			grid.askForHelp();
		}				
	}
	 		
	grid.printGrid("Solved Sudoku");
		
	return 0;
}















