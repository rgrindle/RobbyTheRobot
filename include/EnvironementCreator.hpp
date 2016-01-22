#ifndef ENVIRONEMENTCREATOR_HPP_INCLUDED
#define ENVIRONEMENTCREATOR_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

/**
* @file EnvironementCreator.hpp
*
* @author	RGG
* @date	2014-12-16
*/

//=====================
//	REVISIONS
//=====================

#define FRONT_WALL_BIT	  	  1
#define BACK_WALL_BIT	 	  2
#define LEFT_WALL_BIT		  4
#define RIGHT_WALL_BIT		  8

#define CURRENT_STATE_BIT	 16
#define FRONT_STATE_BIT		 32
#define BACK_STATE_BIT		 64
#define LEFT_STATE_BIT		128
#define RIGHT_STATE_BIT		256

class EnvironementCreator
{
public:
	EnvironementCreator(int h, int w);
	~EnvironementCreator();

	void setDimensions(int h, int w);
	int getWidth();
	int getHeight();
	int getState(int x, int y);
	int getState(std::vector<int> position);
	int getOriginalState(int x, int y);
	int getOriginalState(std::vector<int> position);
	int get4Neighborhood(int x, int y);
	int get4Neighborhood(std::vector<int> position);

	void setState(int x, int y, int state);
	void setState(std::vector<int> position, int state);
//	void setState(std::vector<int>::iterator,state);
	void setOriginalState(int x, int y, int state);
	void setOriginalState(std::vector<int> position, int state);
	void setState(int state, double probability);

	std::vector<int> generateAlgorithm(int commands, int situations);
	void restoreEnvironement();

	friend std::ostream& operator<<(std::ostream& stream, EnvironementCreator& ec);
private:
	int width = 0;
	int height = 0;
	std::vector<std::vector<int> > environement;
	std::vector<std::vector<int> > originalEnvironement;
};

#endif // ENVIRONEMENTCREATOR_HPP_INCLUDED
