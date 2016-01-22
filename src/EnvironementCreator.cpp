#include "EnvironementCreator.hpp"

/**
* @file EnvironementCreator.cpp
*
* @author	RGG
* @date	2014-12-16
*/

//==============
//	REVISIONS
//==============

//=============================================================================
//	Constructor / Destructor
//=============================================================================

EnvironementCreator::EnvironementCreator(int h, int w)
{
	srand(time(NULL));

	this->setDimensions(h,w);
	this->originalEnvironement.resize(w);
	this->environement.resize(w);

	int i;
	for(i = 0; i < w; ++i)	{
		this->environement[i].resize(h);
		this->originalEnvironement[i].resize(h);
	}
}

EnvironementCreator::~EnvironementCreator()
{

}

//=============================================================================
//	Get Functions
//=============================================================================

int EnvironementCreator::getWidth()
{
	return this->width;
}

int EnvironementCreator::getHeight()
{
	return this->height;
}

int EnvironementCreator::getState(int x, int y)
{
	return this->environement[x][y];
}

int EnvironementCreator::getState(std::vector<int> position)
{
	return this->getState(position[0],position[1]);
}

int EnvironementCreator::getOriginalState(int x, int y)
{
	return this->originalEnvironement[x][y];
}

int EnvironementCreator::getOriginalState(std::vector<int> position)
{
	return this->getOriginalState(position[0],position[1]);
}

/*
	Note state of surrounding four spaces including placement of walls
	1 = wall/can
	0 = no wall/no can

	neighborhood position values
	1 	- wall front
	2	- wall behind
	4 	- wall right
	8	- wall left
	16 	- can on current space?
	32	- can on front space?
	64	- can on back space?
	128	- can on right space?
	256	- can on left space?
*/
int EnvironementCreator::get4Neighborhood(int x, int y)
{
	int neighborhood = 0;

	if(y > 0)	{
		if(this->getState(x,y-1))	{
			neighborhood |= FRONT_STATE_BIT;
		}
	}
	else {
		neighborhood |= FRONT_WALL_BIT;
		neighborhood &= ~FRONT_STATE_BIT;
	}

	if(y < this->getHeight()-1)	{
		if(this->getState(x,y+1))	{
			neighborhood |= BACK_STATE_BIT;
		}
	}
	else {
		neighborhood |= BACK_WALL_BIT;
		neighborhood &= ~BACK_STATE_BIT;
	}

	if(x > 0)	{
		if(this->getState(x-1,y))	{
			neighborhood |= LEFT_STATE_BIT;
		}
	}
	else {
		neighborhood |= LEFT_WALL_BIT;
		neighborhood &= ~LEFT_STATE_BIT;
	}

	if(x < this->getWidth()-1)	{
		if(this->getState(x+1,y))	{
			neighborhood |= RIGHT_STATE_BIT;
		}
	}
	else {
		neighborhood |= RIGHT_WALL_BIT;
		neighborhood &= ~RIGHT_STATE_BIT;
	}

	if(this->getState(x,y))	{
		neighborhood |= CURRENT_STATE_BIT;
	}

	return neighborhood;
}

int EnvironementCreator::get4Neighborhood(std::vector<int> position)
{
	// check indices
	return this->get4Neighborhood(position[0],position[1]);
}

//=============================================================================
//	Set Functions
//=============================================================================

void EnvironementCreator::setState(int x, int y, int state)
{
	this->environement[x][y] = state;
}

void EnvironementCreator::setState(std::vector<int> position, int state)
{
	this->setState(position[0],position[1],state);
}

void EnvironementCreator::setOriginalState(int x, int y, int state)
{
	this->originalEnvironement[x][y] = state;
}

void EnvironementCreator::setOriginalState(std::vector<int> position, int state)
{
	this->setOriginalState(position[0],position[1],state);
}

void EnvironementCreator::setState(int state, double probability)
{
	int state1 = 0;
	int state0 = 0;

	std::vector<std::vector<int> >::iterator yIt = environement.begin();
	std::vector<int>::iterator xIt;

	while(yIt != environement.end())	{
		xIt = yIt->begin();
		while(xIt != yIt->end())	{
			if(rand() % 101 < probability*100)	{
				//this->setState(it,state);
				*xIt = state;
				//this->setOriginalState(i,j,state);
				++state1;
			}
			else {
				//this->setState(it,0);
				*xIt = 0;
				//this->setOriginalState(i,j,0);
				++state0;
			}
			++xIt;
		}
		++yIt;
	}

	this->originalEnvironement = this->environement;
	std::cout << "State0: " << state0 << std::endl;
	std::cout << "State1: " << state1 << std::endl;
	std::cout << "% of state 1 is " << (double) state1/(double)(state1+state0)*100.0 << '%' << std::endl;
}

void EnvironementCreator::setDimensions(int h, int w)
{
	width = w;
	height = h;
}

//=============================================================================
//	Operator Overload Functions
//=============================================================================

std::ostream& operator<<(std::ostream& stream, EnvironementCreator& ec)
{
	std::ostringstream out;

	int i;
	int j;
	for(i = 0; i < ec.getHeight(); ++i)	{
		for(j = 0; j < ec.getWidth(); ++j)	{
			out << ec.getState(j,i) << ' ';
		}
		out << std::endl;
	}

	return stream << out.str();
}

//=============================================================================
//	Other Functions
//=============================================================================

std::vector<int> EnvironementCreator::generateAlgorithm(int commands, int situations)
{
	std::vector<int> algorithm;

	algorithm.resize(situations);

	int i;
	for(i = 0; i < algorithm.size(); ++i)	{
		algorithm[i] = rand() % commands;
	}

	return algorithm;
}

void EnvironementCreator::restoreEnvironement()
{
	this->environement = this->originalEnvironement;
}
