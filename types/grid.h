#ifndef GRID_H
#define GRID_H

#include "../constants/constants.h"

#include <string>


class Grid
{
private:
	int id;		
		
public: 
	bool isComplete;
	float newPercentage;
	float oldPercentage;
	Block blockMatrix [GRID_DIM][GRID_DIM];	

	//constructors
	Grid(int id);

	//functions	
	int getPointValue(int pointX, int pointY, int blockX, int blockY);
	float getPercentageComplete(void);
	void loadStartingValues(void);
	void getStartingValues(void);
	void setPointValue(Point &point, int pointValue);
	void findImpossibleValues(Point &point);
	void findPossibleValues(Point &point);
	void findValueBins(Block &block);
	void checkOneValueInList(Point &point);
	void checkPossibilities(void);
	void askForHelp(void);
	void pointCheck(void);
	void blockCheck(void);
	void printGrid(void);
	void printGrid(string gridTitle);
	void printGrid(int pointX, int pointY, int blockX, int blockY);
	
	Point &getPoint(int pointX, int pointY, int blockX, int blockY);
	Block &getBlock(int blockX, int blockY);
};


Grid::Grid(int gridId)
{
	id = gridId;
	isComplete = false;
	newPercentage = 0.1f;
	oldPercentage = 0.0f;
	
	for (int i = 0; i < GRID_DIM; i++)
	{
		for (int j = 0; j < GRID_DIM; j++)
		{
			blockMatrix[i][j] = Block(i, j);
		}
	}
}


void Grid::printGrid(void)
{
	cout << "=============================" << endl;
	for (int i = 0; i < GRID_DIM; i++)								//Block Y Dimension
	{
		for (int j = 0; j < BLOCK_DIM; j++)							//Point Y Dimension
		{	
			for (int k = 0; k < GRID_DIM; k++)						//Block X Dimension
			{
				cout << "|| ";				
				for (int l = 0; l < BLOCK_DIM; l++)					//Point X Dimension
				{
					cout << blockMatrix[k][i].pointMatrix[l][j].getValue() << " ";
					
				}				
			}				
			cout << "|| " << endl;
		}		 
		cout << "=============================" << endl;
	}
}


void Grid::printGrid(string gridTitle)
{
	cout << gridTitle << endl;
	cout << "=============================" << endl;
	for (int i = 0; i < GRID_DIM; i++)								//Block Y Dimension
	{
		for (int j = 0; j < BLOCK_DIM; j++)							//Point Y Dimension
		{	
			for (int k = 0; k < GRID_DIM; k++)						//Block X Dimension
			{
				cout << "|| ";				
				for (int l = 0; l < BLOCK_DIM; l++)					//Point X Dimension
				{
					cout << blockMatrix[k][i].pointMatrix[l][j].getValue() << " ";
					
				}				
			}				
			cout << "|| " << endl;
		}		 
		cout << "=============================" << endl;
	}
}

void Grid::printGrid(int pointX, int pointY, int blockX, int blockY)
{
	cout << "=============================" << endl;
	for (int i = 0; i < GRID_DIM; i++)								//Block Y Dimension
	{
		for (int j = 0; j < BLOCK_DIM; j++)							//Point Y Dimension
		{	
			for (int k = 0; k < GRID_DIM; k++)						//Block X Dimension
			{
				cout << "|| ";				
				for (int l = 0; l < BLOCK_DIM; l++)					//Point X Dimension
				{
					if ((l == pointX) && (j == pointY) && (k == blockX) && (i == blockY))
					{
						cout << "\033[32m" << blockMatrix[k][i].pointMatrix[l][j].getValue() << "\033[37m ";
					}
					else
					{
						cout << blockMatrix[k][i].pointMatrix[l][j].getValue() << " ";
					}										
				}				
			}				
			cout << "|| " << endl;
		}		 
		cout << "=============================" << endl;
	}	
}


void Grid::pointCheck(void)
{
	for (int i = 0; i < GRID_DIM; i++)								//Block Y Dimension
	{
		for (int j = 0; j < BLOCK_DIM; j++)							//Point Y Dimension
		{	
			for (int k = 0; k < GRID_DIM; k++)						//Block X Dimension
			{
				for (int l = 0; l < BLOCK_DIM; l++)					//Point X Dimension
				{
					Point point = blockMatrix[k][i].pointMatrix[l][j];
					
					findImpossibleValues(point);	
					findPossibleValues(point);
					checkOneValueInList(point);					
				}				
			}									
		}		 
	}	
}

void Grid::blockCheck(void)
{
	for (int i = 0; i < GRID_DIM; i++)								//Block Y Dimension
	{
		for (int j = 0; j < BLOCK_DIM; j++)							//Point Y Dimension
		{	
			for (int k = 0; k < GRID_DIM; k++)						//Block X Dimension
			{
				for (int l = 0; l < BLOCK_DIM; l++)					//Point X Dimension
				{
					Point point = blockMatrix[i][j].pointMatrix[k][l];
					
					findImpossibleValues(point);	
					findPossibleValues(point);				
				}				
			}
			findValueBins(getBlock(i,j));									
		}		 
	}	
}


void Grid::findImpossibleValues(Point &point)
{
	if (point.getValue() == NULL_VALUE)
	{
		for (int j = 0; j < GRID_DIM; j++)
		{
			for (int k = 0; k < BLOCK_DIM; k++)
			{

				//perform search in horizontal orientation
				int horizontalPointValue = getPointValue(k, point.getY(), j, point.getBlockY());
				if (!point.isValueInList(horizontalPointValue, point.impossibleValues))		
				{
					point.addValueToList(horizontalPointValue, point.impossibleValues);			
				}
		

				//perform search in vertical orientation
				int verticalPointValue = getPointValue(point.getX(), k, point.getBlockX(), j);
				if (!point.isValueInList(verticalPointValue, point.impossibleValues))		
				{
					point.addValueToList(verticalPointValue, point.impossibleValues);			
				}
				

				//perform block search
				int blockValue = getPointValue(j, k, point.getBlockX(), point.getBlockY());
				if (!point.isValueInList(blockValue, point.impossibleValues))		
				{
					point.addValueToList(blockValue, point.impossibleValues);			
				}					
			}
		}
	}
}


void Grid::findPossibleValues(Point &point)
{
	for (int i = 0; i < MAX_VALUE; i++)
	{
		if (point.impossibleValues[i] > 0)
		{
			point.removeValueFromList(point.impossibleValues[i], point.possibleValues);						
		}
	}
}


Point &Grid::getPoint(int pointX, int pointY, int blockX, int blockY)
{
	return blockMatrix[blockX][blockY].pointMatrix[pointX][pointY];
}


void Grid::setPointValue(Point &point, int pointValue)
{
	blockMatrix[point.getBlockX()][point.getBlockY()].pointMatrix[point.getX()][point.getY()].setValue(pointValue);
	
	if (isVerbose)
	{
		cout << "Point: (" << point.getX() << ", " << point.getY() << "), Block: (" << point.getBlockX() << ", " << point.getBlockY() << "), Value: " << pointValue << "\t(" << getPercentageComplete() << "%)" << endl;
	}
	
}


int Grid::getPointValue(int pointX, int pointY, int blockX, int blockY)
{
	return blockMatrix[blockX][blockY].pointMatrix[pointX][pointY].getValue();
}


void Grid::checkOneValueInList(Point &point)
{
	int countValues = 0;
	int lastValue = 0;
	int *list = point.possibleValues;
	
	for (int i = 0; i < MAX_VALUE; i++)
	{
		if (list[i] > 0)
		{
			lastValue = list[i];
			countValues++;
		} 
	}
	
	if (countValues == 1)
	{
		setPointValue(point, lastValue);
	}
}


float Grid::getPercentageComplete(void)
{	
	int countComplete = 0;
	
	for (int i = 0; i < GRID_DIM; i++)								//Block Y Dimension
	{
		for (int j = 0; j < BLOCK_DIM; j++)							//Point Y Dimension
		{	
			for (int k = 0; k < GRID_DIM; k++)						//Block X Dimension
			{
				for (int l = 0; l < BLOCK_DIM; l++)					//Point X Dimension
				{
					Point point = blockMatrix[k][i].pointMatrix[l][j];
					
					if (point.getValue() != NULL_VALUE)
					{
						countComplete++;
					}							
				}				
			}				
		}		 
	}	
	
	if (countComplete == (float)(BLOCK_DIM*BLOCK_DIM*GRID_DIM*GRID_DIM))
	{
		isComplete = true;
	}
	
	return countComplete/((float)(BLOCK_DIM*BLOCK_DIM*GRID_DIM*GRID_DIM))*100;	
}


void Grid::findValueBins(Block &block)
{
	for (int i = 1; i <= MAX_VALUE; i++) 						//for each digit
	{
		int countValue = 0;
		int lastX, lastY;
				
		for (int k = 0; k < BLOCK_DIM; k++)						//point x dimension
		{
			for (int l = 0; l < BLOCK_DIM; l++)					//point y dimension
			{
				if ((block.getPoint(k,l).isValueInList(i, block.getPoint(k,l).possibleValues)) && (block.getPoint(k,l).getValue() == 0))
				{
					lastX = k;
					lastY = l;
					countValue++;					
				}								
			}				
		}	
		
		if (countValue == 1)
		{
			setPointValue(block.getPoint(lastX, lastY), i);					
		}
		
	}
}

Block &Grid::getBlock(int blockX, int blockY)
{
	return blockMatrix[blockX][blockY];
}

void Grid::getStartingValues(void)
{
	char inputNumber;
	
	system("clear\n");
	//cout << "=============================" << endl;
	for (int i = 0; i < GRID_DIM; i++)								//Block Y Dimension
	{
		for (int j = 0; j < BLOCK_DIM; j++)							//Point Y Dimension
		{	
			for (int k = 0; k < GRID_DIM; k++)						//Block X Dimension
			{
				//cout << "|| ";				
				for (int l = 0; l < BLOCK_DIM; l++)					//Point X Dimension
				{
					
					printGrid(l,j,k,i);
					
					cout << "Point: (" << l << ", " << j << "), Block: (" << k << ", " << i << "), Enter Value: " ;
					cin >> inputNumber;		
					
					while (true)
					{
						if (isdigit(inputNumber))
						{
							inputNumber = inputNumber - '0'; //convert char to int;
							getPoint(l,j,k,i).setValue(inputNumber);
							break;
						}
						cin >> inputNumber;
					} 
				}				
			}				
			//cout << "|| " << endl;
		}		 
		//cout << "=============================" << endl;
	}
}

void Grid::askForHelp(void)
{
	string help;
	cout << "This one is really tricky! Help a brother out?" << endl;
	cout << "This is what I have so far:" << endl;
	printGrid("Partially Solved Sodoku:");
	cout << "And here are some possibilities I found:" << endl;
	checkPossibilities();
	cin >> help;
}

void Grid::loadStartingValues(void)
{
	switch (id)
	{
		case 13:
		{
			getPoint(0,2,0,0).setValue(5);
			getPoint(2,2,0,0).setValue(8);	
			getPoint(1,2,1,0).setValue(2);
			getPoint(2,0,1,0).setValue(9);
			getPoint(0,0,2,0).setValue(5);
			getPoint(0,2,2,0).setValue(9);
			getPoint(2,1,2,0).setValue(8);
			getPoint(1,2,2,0).setValue(6);
			getPoint(0,0,0,1).setValue(2);
			getPoint(0,1,0,1).setValue(1);
			
			getPoint(0,2,0,1).setValue(6);
			getPoint(2,0,0,1).setValue(4);
			getPoint(2,2,0,1).setValue(7);
			getPoint(0,0,1,1).setValue(1);	
			getPoint(0,1,1,1).setValue(7);
			getPoint(2,1,1,1).setValue(5);
			getPoint(2,2,1,1).setValue(8);
			getPoint(0,0,2,1).setValue(7);		
			getPoint(0,2,2,1).setValue(1);
			getPoint(2,0,2,1).setValue(6);
				
			getPoint(2,1,2,1).setValue(3);			
			getPoint(2,2,2,1).setValue(9);
			getPoint(0,1,0,2).setValue(8);
			getPoint(1,0,0,2).setValue(2);
			getPoint(2,0,0,2).setValue(6);
			getPoint(2,2,0,2).setValue(3);	
			getPoint(1,0,1,2).setValue(5);
			getPoint(0,2,1,2).setValue(9);
			getPoint(0,0,2,2).setValue(3);
			getPoint(2,0,2,2).setValue(4);
			break;
		}
		
		case 11:
		{
			getPoint(0,1,0,0).setValue(6);
			getPoint(0,2,0,0).setValue(4);
			getPoint(1,1,0,0).setValue(1);
			getPoint(1,2,0,0).setValue(7);
			getPoint(2,2,0,0).setValue(3);
			getPoint(0,1,1,0).setValue(2);
			getPoint(1,1,1,0).setValue(7);
			getPoint(1,2,1,0).setValue(6);
			getPoint(2,2,1,0).setValue(9);
			getPoint(0,1,0,1).setValue(5);
			
			getPoint(0,2,0,1).setValue(2);
			getPoint(2,0,0,1).setValue(9);
			getPoint(2,1,0,1).setValue(6);
			getPoint(0,0,1,1).setValue(5);
			getPoint(0,1,1,1).setValue(9);
			getPoint(2,1,1,1).setValue(4);
			getPoint(2,2,1,1).setValue(3);
			getPoint(0,1,2,1).setValue(2);
			getPoint(0,2,2,1).setValue(5);
			getPoint(2,0,2,1).setValue(1);			
			
			getPoint(2,1,2,1).setValue(8);
			getPoint(0,0,1,2).setValue(3);
			getPoint(1,0,1,2).setValue(5);
			getPoint(1,1,1,2).setValue(4);
			getPoint(2,1,1,2).setValue(1);
			getPoint(0,0,2,2).setValue(9);
			getPoint(1,0,2,2).setValue(8);
			getPoint(1,1,2,2).setValue(2);
			getPoint(2,0,2,2).setValue(4);
			getPoint(2,1,2,2).setValue(6);
			break;
		}
	}
}

void Grid::checkPossibilities(void)
{
	for (int i = 0; i < GRID_DIM; i++)								//Block Y Dimension
	{
		for (int j = 0; j < BLOCK_DIM; j++)							//Point Y Dimension
		{	
			for (int k = 0; k < GRID_DIM; k++)						//Block X Dimension
			{
				for (int l = 0; l < BLOCK_DIM; l++)					//Point X Dimension
				{
					if (getPoint(k,l,i,j).getValue() == NULL_VALUE) //only display possibilities for nonzero points
					{
						getPoint(k,l,i,j).printList(POSSIBLE);
					}					
				}				
			}				
		}		 
	}	
}

#endif
