#include "RobotRuler.hpp"

std::fstream out("data.txt");

//=============================================================================
//	Constructor / Destructor
//=============================================================================

RobotRuler::RobotRuler(int population, int h, int w)
	:EnvironementCreator(h,w)
{
	this->setState(1,0.5);
	robby__.resize(population,Robot(w,h));

	std::vector<Robot>::iterator it;
	for(it = robby__.begin(); it != robby__.end(); ++it)	{
		it->setAlgorithm(this->generateAlgorithm(6,511));	// not all the numbers will correspond to situations that will actually happen
	}
}

RobotRuler::~RobotRuler()
{

}

//=============================================================================
//	Get Functions
//=============================================================================

const std::vector<int>& RobotRuler::getPosition(int robotIndex)
{
	return this->robby__[robotIndex].getPosition();
}

const int& RobotRuler::getXPosition(int robotIndex)
{
	return this->robby__[robotIndex].getXPosition();
}

const int& RobotRuler::getYPosition(int robotIndex)
{
	return this->robby__[robotIndex].getYPosition();
}

const std::vector<int>& RobotRuler::getAlgorithm(int robotIndex)
{
	return this->robby__[robotIndex].getAlgorithm();
}

const int& RobotRuler::getScore(int robotIndex)
{
	return this->robby__[robotIndex].getScore();
}

const int& RobotRuler::getCansCollected(int robotIndex)
{
	return this->robby__[robotIndex].getCansCollected();
}

const std::vector<int>& RobotRuler::getPosition(std::vector<Robot>::iterator robotIterator)
{
	return robotIterator->getPosition();
}

const int& RobotRuler::getXPosition(std::vector<Robot>::iterator robotIterator)
{
	return robotIterator->getXPosition();
}

const int& RobotRuler::getYPosition(std::vector<Robot>::iterator robotIterator)
{
	return robotIterator->getYPosition();
}

const std::vector<int>& RobotRuler::getAlgorithm(std::vector<Robot>::iterator robotIterator)
{
	return robotIterator->getAlgorithm();
}

const int& RobotRuler::getScore(std::vector<Robot>::iterator robotIterator)
{
	return robotIterator->getScore();
}

const int& RobotRuler::getCansCollected(std::vector<Robot>::iterator robotIterator)
{
	return robotIterator->getCansCollected();
}

const int& RobotRuler::getMoves()
{
	return this->moves__;
}

const int& RobotRuler::getMax()
{
	return this->max__;
}

const int& RobotRuler::getMin()
{
	return this->min__;
}

const int& RobotRuler::getAverage()
{
	return this->avg__;
}

std::string RobotRuler::getTimeString()
{
	char name[20];
	time_t now = time(0);

	strftime(name,sizeof(name),"%Y-%m-%d_%H-%M-%S",localtime(&now));

	return std::string(name);
}

//=============================================================================
//	Set Functions
//=============================================================================

void RobotRuler::setPosition(int robotIndex, int x, int y)
{
	this->robby__[robotIndex].setPosition(x,y);
}

void RobotRuler::setPosition(int robotIndex, std::vector<int> position)
{
	this->robby__[robotIndex].setPosition(position);
}

void RobotRuler::setXPosition(int robotIndex, int x)
{
	this->robby__[robotIndex].setXPosition(x);
}

void RobotRuler::setYPosition(int robotIndex, int y)
{
	this->robby__[robotIndex].setYPosition(y);
}

void RobotRuler::changeScore(int robotIndex, int changeFactor)
{
	this->robby__[robotIndex].changeScore(changeFactor);
}

void RobotRuler::increaseCansCollected(int robotIndex)
{
	this->robby__[robotIndex].increaseCansCollected();
}

void RobotRuler::setPosition(std::vector<Robot>::iterator robotIterator, int x, int y)
{
	robotIterator->setPosition(x,y);
}

void RobotRuler::setPosition(std::vector<Robot>::iterator robotIterator, std::vector<int> position)
{
	robotIterator->setPosition(position);
}

void RobotRuler::setXPosition(std::vector<Robot>::iterator robotIterator, int x)
{
	robotIterator->setXPosition(x);
}

void RobotRuler::setYPosition(std::vector<Robot>::iterator robotIterator, int y)
{
	robotIterator->setYPosition(y);
}

void RobotRuler::changeScore(std::vector<Robot>::iterator robotIterator, int changeFactor)
{
	robotIterator->changeScore(changeFactor);
}

void RobotRuler::increaseCansCollected(std::vector<Robot>::iterator robotIterator)
{
	robotIterator->increaseCansCollected();
}

void RobotRuler::setMoves(int moves)
{
	this->moves__ = moves;
}

void RobotRuler::saveAlgorithm(int robotIndex)
{
	this->robby__[robotIndex].saveAlgorithm();
}

void RobotRuler::saveAlgorithm(std::vector<Robot>::iterator robotIterator)
{
	robotIterator->saveAlgorithm();
}

//=============================================================================
//	Other Functions
//=============================================================================

void RobotRuler::saveAlgorithmList()
{
	std::vector<Robot>::iterator robotIterator;
	std::ofstream out;
	std::string filename = "./data/algorithm/algorithmList";

	//filename.append(this->getDateString());
	filename.append(this->getTimeString());
	filename.append(".txt");
	out.open(filename.c_str(), std::ofstream::out);

	if(out.is_open())	{
		for(robotIterator = robby__.begin(); robotIterator != robby__.end(); ++robotIterator)	{
			std::vector<int> al = robotIterator->getAlgorithm();
			std::vector<int>::iterator it;
			out << std::distance(robby__.begin(),robotIterator) << ".";
			for(it = al.begin(); it != al.end(); ++it)	{
				out << *it;
			}
			out << std::endl << std::endl;

		}
		out.close();
	}
	else {
		// throw exception
	}
}

void RobotRuler::performCommand(std::vector<Robot>::iterator robotIterator, int cmd)
{
	int movement;

	switch(cmd)
	{
		case MOVE_FORWARD:
			if(robotIterator->get4Neighborhood() & FRONT_WALL_BIT)	{
				robotIterator->changeScore(WALL_HIT);
			}
			else {
				robotIterator->setYPosition(robotIterator->getYPosition()-1);
			}
			break;
		case MOVE_BACKWARD:
			if(robotIterator->get4Neighborhood() & BACK_WALL_BIT)	{
				robotIterator->changeScore(WALL_HIT);
			}
			else {
				robotIterator->setYPosition(robotIterator->getYPosition()+1);
			}
			break;
		case MOVE_LEFT:
			if(robotIterator->get4Neighborhood() & LEFT_WALL_BIT)	{
				robotIterator->changeScore(WALL_HIT);
			}
			else {
				robotIterator->setXPosition(robotIterator->getXPosition()-1);
			}
			break;
		case MOVE_RIGHT:
			if(robotIterator->get4Neighborhood() & RIGHT_WALL_BIT)	{
				robotIterator->changeScore(WALL_HIT);
			}
			else {
				robotIterator->setXPosition(robotIterator->getXPosition()+1);
			}
			break;
		case MOVE_RANDOM:
			movement = rand() % 4;

			switch(movement)
			{
				case MOVE_FORWARD:
					if(robotIterator->get4Neighborhood() & FRONT_WALL_BIT)	{
						robotIterator->changeScore(WALL_HIT);
					}
					else {
						robotIterator->setYPosition(robotIterator->getYPosition()-1);
					}
					break;
				case MOVE_BACKWARD:
					if(robotIterator->get4Neighborhood() & BACK_WALL_BIT)	{
						robotIterator->changeScore(WALL_HIT);
					}
					else {
						robotIterator->setYPosition(robotIterator->getYPosition()+1);
					}
					break;
				case MOVE_LEFT:
					if(robotIterator->get4Neighborhood() & LEFT_WALL_BIT)	{
						robotIterator->changeScore(WALL_HIT);
					}
					else {
						robotIterator->setXPosition(robotIterator->getXPosition()-1);
					}
					break;
				case MOVE_RIGHT:
					if(robotIterator->get4Neighborhood() & RIGHT_WALL_BIT)	{
						robotIterator->changeScore(WALL_HIT);
					}
					else {
						robotIterator->setXPosition(robotIterator->getXPosition()+1);
					}
					break;
			}
			break;
		case REMOVE_CAN:
			if(EnvironementCreator::getState(robotIterator->getPosition()) == CAN)	{
				robotIterator->increaseCansCollected();
				EnvironementCreator::setState(robotIterator->getPosition(),NO_CAN);
				robotIterator->changeScore(CAN_COLLECTED);
			}
			else {
				robotIterator->changeScore(CAN_NOT_COLLECTED);
			}
			break;
	}
}

void RobotRuler::simulateGeneration(int moves, int seasons)
{
	this->setMoves(moves);
	std::vector<Robot>::iterator it;
	int i;

	for(it = robby__.begin(); it != robby__.end(); ++it)	{
		int sum = 0;

		for(i = 0; i < seasons; ++i)	{
			int j;

			for(j = 0; j < moves; ++j)	{
				std::vector<int> al = it->getAlgorithm();
				int n = EnvironementCreator::get4Neighborhood(it->getPosition());
				it->set4Neighborhood(n);
				this->performCommand(it,al[n]);
			}
			EnvironementCreator::restoreEnvironement();
			it->setPosition(rand() % EnvironementCreator::getWidth(), rand() % EnvironementCreator::getHeight());
			sum += it->getScore();
			it->setScore(0);
			it->setCansCollected(0);
		}
		it->setScore((double)sum/(double)seasons);
	}
}

void RobotRuler::rankRobots()
{
	std::vector<Robot>::iterator it;
	int m = this->getMoves();
	int minimum = CAN_COLLECTED*m;
	int maximum = std::min(WALL_HIT*m,CAN_NOT_COLLECTED*m);
	int sum = 0;
	int counter = 0;
	int score;

	std::sort(robby__.begin(),robby__.end(),compScore);

	for(it = robby__.begin(); it != robby__.end(); ++it, ++counter)	{
		score = it->getScore();
		//std::cout << score << ' ';
		if(score > maximum)	{
			maximum = score;
		}
		if(score < minimum)	{
			minimum = score;
		}
		sum += score;
	}
	this->avg__ = (double) sum/counter;
	this->min__ = minimum;
	this->max__ = maximum;

	out << this->min__ << ',';
	out << this->avg__ << ',';
	out << this->max__ << ',' << std::endl;
}

bool compScore(Robot r1, Robot r2)
{
	return (r1.getScore() > r2.getScore());
}

bool compPercent(pairer p1, pairer p2)
{
	return (p1.percent > p2.percent);
}

void RobotRuler::mate()
{
	std::vector<pairer> pairs;
	pairs.resize(this->robby__.size());
	std::vector<pairer>::iterator pairIt;

	for(pairIt = pairs.begin(); pairIt != pairs.end(); ++pairIt)	{
		(*pairIt).firstIndex = rand() % this->robby__.size();
		(*pairIt).secondIndex = rand() % this->robby__.size();

		while((*pairIt).firstIndex == (*pairIt).secondIndex)	{
			(*pairIt).secondIndex = rand() % this->robby__.size();
		}
		//std::cout << (*pairIt).firstIndex << ' ' << (*pairIt).secondIndex << std::endl;
		// -1000 500 -> range = 1500 -> % = (score+1000)/1500
		(*pairIt).percent = (double)((this->robby__[(*pairIt).firstIndex].getScore()+1000.0d)*(this->robby__[(*pairIt).secondIndex].getScore()+1000.0d))/2250000.0d;
		//std::cout << (*pairIt).percent << std::endl;
	}

	std::sort(pairs.begin(),pairs.end(),compPercent);

//	std::vector<pairer>::iterator ilk;

//	for(ilk = pairs.begin(); ilk != pairs.end(); ++ilk)	{
//		std::cout << (*ilk).percent << ' ';
//	}

	std::vector<Robot> tmp;
	tmp.resize(this->robby__.size(),Robot());
	std::vector<Robot>::iterator tmpIt;
//	std::vector<int>::iterator algIt;
	std::vector<int> newAlg;
	newAlg.resize(this->robby__[0].getAlgorithm().size());
	std::vector<int> alg1;
	std::vector<int> alg2;
	int choose;
	int counter;
	int babies;

	for(counter = 0, tmpIt = tmp.begin(), pairIt = pairs.begin(); tmpIt != tmp.end(); ++tmpIt, ++pairIt, ++counter)	{
		if(counter < 20)	{
			babies = 4;
		}
		else	{
			babies = 2;
		}

		for( ; babies > 0; --babies)	{
			alg1 = this->robby__[(*pairIt).firstIndex].getAlgorithm();
			alg2 = this->robby__[(*pairIt).secondIndex].getAlgorithm();
			int i;

			for(i = 0; i < newAlg.size(); ++i)	{
				choose = rand() % 100 + 1;

				// mutate at rate of 2%
				if(choose > 51)	{
					newAlg[i] = alg1[i];	// mom's gene
				}
				else if(choose > 2)	{
					newAlg[i] = alg2[i];	// dad's gene
				}
				else	{
					newAlg[i] = rand() % 6;	// mutated gene
				}
			}
			tmpIt->setAlgorithm(newAlg);
			//std::cout << (*pairIt).percent << std::endl;
		}
	}

	std::vector<Robot>::iterator robbyIt;

	for(robbyIt = this->robby__.begin(), tmpIt = tmp.begin(); robbyIt != this->robby__.end(); ++robbyIt, ++tmpIt)	{
		//RGG: problem line. I don't know why!
		//std::vector<int> algorithm = tmpIt->getAlgorithm();
		//robbyIt->setAlgorithm(algorithm);
		robbyIt->setAlgorithm(tmpIt->getAlgorithm());
		robbyIt->setCansCollected(0);
		robbyIt->setScore(0);
	}
}
