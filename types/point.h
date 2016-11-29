#ifndef POINT_H
#define POINT_H

#include "../constants/constants.h"

#include <iostream>
#include <ctype.h>

using namespace std;

class Point
{
private:	
	int x, y;	
	int value;
	int blockX, blockY;
	bool isConstant;

public:
	int *impossibleValues = (int*)malloc(MAX_VALUE*sizeof(int));
	int *possibleValues = (int*)malloc(MAX_VALUE*sizeof(int));

	//constructors
	Point();
	Point(int pX, int pY, int bX, int bY);
	
	//functions
	int getX(void){return x;};
	int getY(void){return y;};
	int getValue(void){return value;};
	int getBlockX(void){return blockX;};
	int getBlockY(void){return blockY;};	
	
	void printPoint(void);	
	void setValue(int pointValue);
	
	void initLists(void);
	void printList(LIST list);
		
	void addValueToList(int value, int *list);
	void removeValueFromList(int value, int *list);	
	bool isValueInList(int value, int *list);	

};
	
Point::Point()
{
	
}

Point::Point(int pX, int pY, int bX, int bY)
{
	x = pX; 
	y = pY; 
	blockX = bX;
	blockY = bY;
	value = 0;
	isConstant = false;
	initLists();
}


void Point::printPoint(void)
{
	cout << "Point: (" << x << ", " << y << "), Block: " << "( " << blockX << ", " << blockY << "), Value: " << value << ", Constant:  " << isConstant << endl;
}


void Point::printList(LIST list)
{
	switch (list)
	{
		case POSSIBLE:
			cout << "Possible values for point(" << x << ", " << y << "), block(" << blockX << ", " << blockY << ") : "; 
			for (int i = 0; i < MAX_VALUE; i++)
			{
				cout << possibleValues[i] << " ";
			}
			cout << endl;
			break;
			
		case IMPOSSIBLE:
			cout << "Impossible values for (" << x << ", " << y << "), block(" << blockX << ", " << blockY << ") : "; 
			for (int i = 0; i < MAX_VALUE; i++)
			{
				cout << impossibleValues[i] << " ";
			}
			cout << endl;
			break;					
	}
}


void Point::initLists(void)
{
	for (int i = 0; i < MAX_VALUE; i++)
	{
		impossibleValues[i] = 0;
		possibleValues[i] = i + 1;
	}
}


void Point::setValue(int pointValue)
{
	if ((pointValue >= 1) && (pointValue <= 9))
	{
		value = pointValue;		
	} 
	else
	{
		//print error message
	}
}


void Point::addValueToList(int value, int *list)
{
	for (int i = 0; i < MAX_VALUE; i++)
	{
		if (list[i] == NULL_VALUE)
		{
			list[i] = value;
			break;
		}
	}
}


void Point::removeValueFromList(int value, int *list)
{
	for (int i = 0; i < MAX_VALUE; i++)
	{
		if (list[i] == value)
		{
			list[i] = 0;
			break;
		}
	}
}


bool Point::isValueInList(int value, int *list)
{
	for (int i = 0; i < MAX_VALUE; i++)
	{
		if (list[i] == value)
		{
			return true;
		}
	}
	
	return false;
}



#endif
