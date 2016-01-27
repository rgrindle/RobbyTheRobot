#ifndef ROBOT_HPP_INCLUDED
#define ROBOT_HPP_INCLUDED

#include <vector>
#include <fstream>
#include <time.h>
#include <string>
#include <stdlib.h>

class Robot
{
public:
	Robot();
	Robot(int xMax, int yMax);
	~Robot();

	void setPosition(int x, int y);
	void setXPosition(int x);
	void setYPosition(int y);
	void setPosition(std::vector<int> position);
	void set4Neighborhood(int nbhd);
	void setAlgorithm(std::vector<int> algrthm);
	void changeScore(int changeFactor);
	void increaseCansCollected();
	void setCansCollected(int numberOfCans);
	void setScore(int score);

	const std::vector<int>& getPosition();
	const std::vector<int>& getAlgorithm();
	const int& getScore();
	const int& getCansCollected();
	const int& get4Neighborhood();
	const int& getXPosition();
	const int& getYPosition();

private:
	std::vector<int> pos__;
	std::vector<int> algorithm__;
	int neighborhood__;
	int cansCollected__;
	int score__;
};

#endif // ROBOT_HPP_INCLUDED
