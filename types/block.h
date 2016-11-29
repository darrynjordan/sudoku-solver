#ifndef BLOCK_H
#define BLOCK_H

#include "../constants/constants.h"

class Block
{
private:
	int x, y;

public:	
	Point pointMatrix [BLOCK_DIM][BLOCK_DIM];

	//constructors
	Block(void);
	Block(int blockX, int blockY);
	
	//functions
	int getX(void){return x;};
	int getY(void){return y;};
	Point &getPoint(int pointX, int pointY);
};

Block::Block(void)
{
	
}


Block::Block(int blockX, int blockY)
{
	x = blockX;
	y = blockY;
	
	for (int i = 0; i < BLOCK_DIM; i++)
	{
		for (int j = 0; j < BLOCK_DIM; j++)
		{
			pointMatrix[i][j] = Point(i, j, x, y);  //local position (relative to block)
		}
	}
}


Point &Block::getPoint(int pointX, int pointY)
{
	return pointMatrix[pointX][pointY];
}

#endif
