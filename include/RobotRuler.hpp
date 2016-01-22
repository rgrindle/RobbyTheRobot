#ifndef ROBOTRULER_HPP_INCLUDED
#define ROBOTRULER_HPP_INCLUDED

#include "EnvironementCreator.hpp"
#include "RobotCreator.hpp"
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

#define CAN				1
#define NO_CAN			0

#define WALL			1
#define NO_WALL			0

#define MOVE_FORWARD	0
#define MOVE_BACKWARD	1
#define MOVE_LEFT		2
#define MOVE_RIGHT		3
#define MOVE_RANDOM		4
#define REMOVE_CAN		5

#define CAN_COLLECTED		10
#define CAN_NOT_COLLECTED	-1
#define WALL_HIT			-5

class pairer
{
public:
	int firstIndex;
	int secondIndex;
	double percent;
	unsigned int numberOfBabies;
};

bool compScore(Robot r1, Robot r2);
bool compPercent(pairer p1, pairer p2);

class RobotRuler: public EnvironementCreator
{
public:
	RobotRuler(int population, int h, int w);
	RobotRuler(int population, int h, int w, std::string algorithmFileLocation, std::string scoreDataName);
	~RobotRuler();

	void performCommand(std::vector<Robot>::iterator robotIterator, int cmd);
	void performCommand(std::vector<Robot>::iterator robotIterator, int cmd, std::vector<std::vector<int> > env); // parallel processing version
	void simulateGeneration(int moves, int seasons);
	void singleThreadedGenerations(int seasons);
	void multiThreadedGenerations(std::vector<std::vector<int> > env, int moves, int seasons, int numOfCores, int coreNum);  // parallel processing version
	void rankRobots();
	void mate();

	const std::vector<int>& getPosition(int robotIndex);
	const int& getXPosition(int robotIndex);
	const int& getYPosition(int robotIndex);
	const std::vector<int>& getAlgorithm(int robotIndex);
	const int& getScore(int robotIndex);
	const int& getCansCollected(int robotIndex);
	//const int& get4Neighborhood(int robotIndex);
	const std::vector<int>& getPosition(std::vector<Robot>::iterator robotIterator);
	const int& getXPosition(std::vector<Robot>::iterator robotIterator);
	const int& getYPosition(std::vector<Robot>::iterator robotIterator);
	const std::vector<int>& getAlgorithm(std::vector<Robot>::iterator robotIterator);
	const int& getScore(std::vector<Robot>::iterator robotIterator);
	const int& getCansCollected(std::vector<Robot>::iterator robotIterator);
	//const int& get4Neighborhood(std::vector<Robot>::iterator robotIterator);
	const int& getMoves();
	const int& getMax();
	const int& getMin();
	const int& getAverage();
	std::string getTimeString();
	double getMedianScore();

	void setPosition(int robotIndex, int x, int y);
	void setPosition(int robotIndex, std::vector<int> position);
	void setXPosition(int robotIndex, int x);
	void setYPosition(int robotIndex, int y);
	void changeScore(int robotIndex, int changeFactor);
	void increaseCansCollected(int robotIndex);
	void setPosition(std::vector<Robot>::iterator robotIterator, int x, int y);
	void setPosition(std::vector<Robot>::iterator robotIterator, std::vector<int> position);
	void setXPosition(std::vector<Robot>::iterator robotIterator, int x);
	void setYPosition(std::vector<Robot>::iterator robotIterator, int y);
	void changeScore(std::vector<Robot>::iterator robotIterator, int changeFactor);
	void increaseCansCollected(std::vector<Robot>::iterator robotIterator);
	void setMoves(int moves);

	void saveAlgorithmList();
	void saveAlgorithm(int robotIndex);
	void saveAlgorithm(std::vector<Robot>::iterator robotIterator);

	void printScore();

	std::ofstream scoreOut;
	std::ofstream algorithmOut;

private:
	std::vector<Robot> robby__;
	int moves__;
	double avg__;
	int min__;
	int max__;
	double median__;
	int generation__;
};

#endif // ROBOTRULER_HPP_INCLUDED
