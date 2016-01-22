#include "RobotCreator.hpp"

//=============================================================================
//	Constructor / Destructor
//=============================================================================

Robot::Robot()
	:score__(0),cansCollected__(0)
{
	this->pos__.resize(2);
}

Robot::Robot(int xMax, int yMax)
	:score__(0),cansCollected__(0)
{
	srand(0);
	this->pos__.resize(2);
	this->setPosition(rand() % xMax, rand() % yMax);
}

Robot::~Robot()
{

}

//=============================================================================
//	Get Functions
//=============================================================================

const std::vector<int>& Robot::getPosition()
{
	return this->pos__;
}

const std::vector<int>& Robot::getAlgorithm()
{
	return this->algorithm__;
}

const int& Robot::getScore()
{
	return this->score__;
}

const int& Robot::getCansCollected()
{
	return this->cansCollected__;
}

const int& Robot::get4Neighborhood()
{
	return this->neighborhood__;
}

const int& Robot::getXPosition()
{
	return this->pos__[0];
}

const int& Robot::getYPosition()
{
	return this->pos__[1];
}

//std::string Robot::getDateString()
//{
//	time_t now;
//	char date[12];
//
//	date[0] = '\0';
//
//	now = time(NULL);
//
//	if(now != -1)	{
//		strftime(date,12,"%d_%m_%Y",gmtime(&now));
//	}
//
//	return std::string(date);
//}

//std::string Robot::getTimeString()
//{
//	char name[20];
//	time_t now = time(0);
//
//	strftime(name,sizeof(name),"%Y-%m-%d_%H-%M-%S",localtime(&now));
//
//	return std::string(name);
//}

//=============================================================================
//	Set Functions
//=============================================================================

void Robot::setPosition(int x, int y)
{
	this->pos__[0] = x;
	this->pos__[1] = y;
}

void Robot::setXPosition(int x)
{
	this->pos__[0] = x;
}

void Robot::setYPosition(int y)
{
	this->pos__[1] = y;
}

void Robot::setPosition(std::vector<int> position)
{
	if(position.size() != 2)	{
		// throw exception
	}
	else {
		this->setPosition(position[0],position[1]);
	}
}

void Robot::set4Neighborhood(int nbhd)
{
	this->neighborhood__ = nbhd;
}

void Robot::changeScore(int changeFactor)
{
	this->score__ += changeFactor;
}

void Robot::increaseCansCollected()
{
	++(this->cansCollected__);
}

void Robot::setAlgorithm(std::vector<int> algrthm)
{
	this->algorithm__ = algrthm;
}

void Robot::saveAlgorithm()
{
	std::ofstream out;
	std::string filename = "./data/algorithm/algorithm";

	//filename.append(this->getDateString());
	//filename.append(this->getTimeString());
	filename.append(".txt");
	out.open(filename.c_str(), std::ofstream::out);

	if(out.is_open())	{
		std::vector<int> al = this->getAlgorithm();
		std::vector<int>::iterator it;

		for(it = al.begin(); it != al.end(); ++it)	{
			out << *it;
		}
		out.close();
	}
	else {
		// throw exception
	}
}

void Robot::setCansCollected(int numberOfCans)
{
	this->cansCollected__ = numberOfCans;
}

void Robot::setScore(int score)
{
	this->score__ = score;
}
