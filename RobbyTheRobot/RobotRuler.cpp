#include "RobotRuler.hpp"

//=============================================================================
//	Constructor / Destructor
//=============================================================================

RobotRuler::RobotRuler(int population, int h, int w)
	:EnvironementCreator(h,w)
{
	scoreOut.open("data/score/score_data.csv");

	scoreOut << "Generation," << "Minimum," << "Average," << "Median," << "Maximum,";

	//algorithmOut.open("./data/algorithm/algorithm_data.csv", std::ofstream::out);

	this->setState(1,0.5);
	robby__.resize(population,Robot(w,h));

	std::vector<Robot>::iterator it;
	for(it = robby__.begin(); it != robby__.end(); ++it)	{
		it->setAlgorithm(this->generateAlgorithm(6,511));	// not all the numbers will correspond to situations that will actually happen
	}

	this->generation__ = 0;
}

RobotRuler::RobotRuler(int population, int h, int w, std::string algorithmFileLocation, std::string scoreDataName)
	:EnvironementCreator(h, w)
{
	// get generation number
	std::ifstream scoreIn("data/score/" + scoreDataName + ".csv");

	if (scoreIn.is_open()) {
		scoreIn.seekg(-1, std::ios_base::end);                // go to one spot before the EOF

		bool keepLooping = true;

		while (keepLooping) {
			char ch;
			scoreIn.get(ch);                            // Get current byte's data

			if ((int)scoreIn.tellg() <= 1) {             // If the data was at or before the 0th byte
				scoreIn.seekg(0);                       // The first line is the last line
				keepLooping = false;                // So stop there
			}
			else if (ch == '\n') {                   // If the data was a newline
				keepLooping = false;                // Stop at the current position.
			}
			else {                                  // If the data was neither a newline nor at the 0 byte
				scoreIn.seekg(-2, std::ios_base::cur);        // Move to the front of that data, then to the front of the data before it
			}
		}
	}

	std::string lastLine;
	std::getline(scoreIn, lastLine);                      // Read the current line
	std::cout << "Result: " << lastLine << '\n';     // Display it
	std::string generator = lastLine.substr(0, lastLine.find(','));
	std::cout << "Generator: " << generator << std::endl;
	int gen = stoi(generator);
	std::cout << "Generator: " << gen << std::endl;
	this->generation__ = gen+1;
	scoreIn.close();
	
	scoreOut.open("data/score/"+scoreDataName+".csv", std::ofstream::app);

	this->setState(1, 0.5);
	robby__.resize(population, Robot(w, h));

	// set up algorithms
	std::ifstream algorithmIn(algorithmFileLocation + "/generation" + generator + ".csv", std::ofstream::out);

	std::vector<int> algorithm(512);
	std::vector<int>::iterator alIt;

	std::vector<Robot>::iterator it;
	for (it = robby__.begin(); it != robby__.end(); ++it) {
		std::string currentAlgorithm;
		getline(algorithmIn, currentAlgorithm);

		for (alIt = algorithm.begin(); alIt < algorithm.end() && !currentAlgorithm.empty(); ++alIt) {
			int comma = currentAlgorithm.find(',');
			*alIt = stoi(currentAlgorithm.substr(0, comma));
			currentAlgorithm.erase(0, comma+1);
		}
		it->setAlgorithm(algorithm);
	}
}

RobotRuler::~RobotRuler()
{
	scoreOut.close();
	algorithmOut.close();
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

//std::string RobotRuler::getTimeString()
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
	//std::ofstream out;

	std::ostringstream generationNumberString;
	generationNumberString << this->generation__;

	algorithmOut.open("./data/algorithm/generation" + generationNumberString.str() + ".csv", std::ofstream::out);

//	if (algorithmOut.is_open())	{
		for(robotIterator = robby__.begin(); robotIterator != robby__.end(); ++robotIterator)	{
			std::vector<int> al = robotIterator->getAlgorithm();

			std::vector<int>::iterator it;
			//algorithmOut << std::distance(robby__.begin(), robotIterator) << ".";

			for(it = al.begin(); it != al.end(); ++it)	{
				algorithmOut << *it << ',';
			}
			algorithmOut << std::endl;
		}
		algorithmOut.close();
//	}
//	else {
		// throw exception
//	}
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

void RobotRuler::performCommand(std::vector<Robot>::iterator robotIterator, int cmd, std::vector<std::vector<int> > env)
{
	int movement;

	switch (cmd)
	{
	case MOVE_FORWARD:
		if (robotIterator->get4Neighborhood() & FRONT_WALL_BIT)	{
			robotIterator->changeScore(WALL_HIT);
		}
		else {
			robotIterator->setYPosition(robotIterator->getYPosition() - 1);
		}
		break;
	case MOVE_BACKWARD:
		if (robotIterator->get4Neighborhood() & BACK_WALL_BIT)	{
			robotIterator->changeScore(WALL_HIT);
		}
		else {
			robotIterator->setYPosition(robotIterator->getYPosition() + 1);
		}
		break;
	case MOVE_LEFT:
		if (robotIterator->get4Neighborhood() & LEFT_WALL_BIT)	{
			robotIterator->changeScore(WALL_HIT);
		}
		else {
			robotIterator->setXPosition(robotIterator->getXPosition() - 1);
		}
		break;
	case MOVE_RIGHT:
		if (robotIterator->get4Neighborhood() & RIGHT_WALL_BIT)	{
			robotIterator->changeScore(WALL_HIT);
		}
		else {
			robotIterator->setXPosition(robotIterator->getXPosition() + 1);
		}
		break;
	case MOVE_RANDOM:
		movement = rand() % 4;

		switch (movement)
		{
		case MOVE_FORWARD:
			if (robotIterator->get4Neighborhood() & FRONT_WALL_BIT)	{
				robotIterator->changeScore(WALL_HIT);
			}
			else {
				robotIterator->setYPosition(robotIterator->getYPosition() - 1);
			}
			break;
		case MOVE_BACKWARD:
			if (robotIterator->get4Neighborhood() & BACK_WALL_BIT)	{
				robotIterator->changeScore(WALL_HIT);
			}
			else {
				robotIterator->setYPosition(robotIterator->getYPosition() + 1);
			}
			break;
		case MOVE_LEFT:
			if (robotIterator->get4Neighborhood() & LEFT_WALL_BIT)	{
				robotIterator->changeScore(WALL_HIT);
			}
			else {
				robotIterator->setXPosition(robotIterator->getXPosition() - 1);
			}
			break;
		case MOVE_RIGHT:
			if (robotIterator->get4Neighborhood() & RIGHT_WALL_BIT)	{
				robotIterator->changeScore(WALL_HIT);
			}
			else {
				robotIterator->setXPosition(robotIterator->getXPosition() + 1);
			}
			break;
		}
		break;
	case REMOVE_CAN:
		if (env[robotIterator->getXPosition()][robotIterator->getYPosition()] == CAN)	{
			robotIterator->increaseCansCollected();
			env[robotIterator->getXPosition()][robotIterator->getYPosition()] = NO_CAN;
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

	auto start = std::chrono::system_clock::now();
#if 0	// to thread or not to thread... (more accurately is threading really helping?)
	unsigned int cores = std::thread::hardware_concurrency();

	std::cout << cores << " cores" << std::endl;

	if (cores <= 1)	{
		singleThreadedGenerations(seasons);
	}
	else {
		std::vector<std::thread> threads;
		int i;
		std::vector<std::vector<int> > env = EnvironementCreator::getOriginalEnvironement();


		// each thread will do every coreth robot
		for (i = 0; i < cores; ++i)	{
			threads.push_back(std::thread(&RobotRuler::multiThreadedGenerations, this, env, moves, seasons, cores, i));
		}
		// join all threads
		for (std::vector<std::thread>::iterator it = threads.begin(); it < threads.end(); ++it)	{
			it->join();
		}
	}
#else
	singleThreadedGenerations(seasons);
#endif
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
	std::cout << duration.count() << " ms" << '\t';
}

void RobotRuler::multiThreadedGenerations(std::vector<std::vector<int> > env, int moves, int seasons, int numOfCores, int coreNum)
{
	std::vector<std::vector<int> > envCurrent = env;

	for (std::vector<Robot>::iterator it = robby__.begin() + coreNum; it < robby__.end(); it += numOfCores)	{
		int sum = 0;
		// run through every season
		for (int i = 0; i < seasons; ++i)	{
			// run through every move within each season
			for (int j = 0; j < moves; ++j)	{
				std::vector<int> al = it->getAlgorithm();
				int n = EnvironementCreator::get4Neighborhood(it->getPosition(),envCurrent);
//				int n = 10;
				it->set4Neighborhood(n);
				this->performCommand(it, al[n], envCurrent);
			}
			envCurrent = env; // restore environement
			it->setPosition(rand() % env.size(), rand() % env[0].size()); // set random start postion
			sum += it->getScore();	// keep a running sum to be average at the end
			// reset score
			it->setScore(0);
			it->setCansCollected(0);
		}
		//std::cout << it - robby__.begin() << std::endl; //RGG 12/31
		// average the final results and set as individual score
		it->setScore((double)sum / (double)seasons);
	}
}

void RobotRuler::singleThreadedGenerations(int seasons)
{
	for (std::vector<Robot>::iterator it = robby__.begin(); it != robby__.end(); ++it)	{
		int sum = 0;

		for (int i = 0; i < seasons; ++i)	{
			for (int j = 0; j < this->getMoves(); ++j)	{
				std::vector<int> al = it->getAlgorithm();
				int n = EnvironementCreator::get4Neighborhood(it->getPosition());
				it->set4Neighborhood(n);
				this->performCommand(it, al[n]);
			}
			EnvironementCreator::restoreEnvironement();
			it->setPosition(rand() % EnvironementCreator::getWidth(), rand() % EnvironementCreator::getHeight());
			sum += it->getScore();
			it->setScore(0);
			it->setCansCollected(0);
		}
		it->setScore((double)sum / (double)seasons);
	}
}

void RobotRuler::rankRobots()
{
	//std::fstream out("data.txt");

	std::vector<Robot>::iterator it;
	int m = this->getMoves();

	// init min and max opposite 
	int minimum = CAN_COLLECTED*m;
	int maximum = std::min(WALL_HIT*m,CAN_NOT_COLLECTED*m);

	int sum = 0;
	int counter = 0;
	int score;

	// organize robots from max to min score
	std::sort(robby__.begin(),robby__.end(),compScore);

	for(it = robby__.begin(); it != robby__.end(); ++it, ++counter)	{
		score = it->getScore();
		//std::cout << score << std::endl;
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
	this->median__ = getMedianScore();
}

void RobotRuler::printScore()
{
	std::cout << " for Generation " << this->generation__ << '\t' << this->min__ << '\t' << this->avg__ << '\t' << this->median__ << '\t' << this->max__ << std::endl;

	scoreOut << std::endl;
	scoreOut << this->generation__ << ',';
	scoreOut << this->min__ << ',';
	scoreOut << this->avg__ << ',';
	scoreOut << this->median__ << ',';
	scoreOut << this->max__ << ',';

	++generation__;
}

bool compScore(Robot r1, Robot r2)
{
	return (r1.getScore() > r2.getScore());
}

bool compPercent(pairer p1, pairer p2)
{
	return (p1.percent > p2.percent);
}

double RobotRuler::getMedianScore()
{
	double median;
	int size = this->robby__.size();
	// assuming that data is already sorted

	if (size % 2 == 0)
	{
		median = (this->robby__[size/2-1].getScore() + this->robby__[size / 2].getScore()) / 2;
	}
	else
	{
		median = this->robby__[(int)size / 2].getScore();
	}

	return median;
}

void RobotRuler::mate()
{
	std::vector<pairer> pairs;
	int start;
	int sum;
	int numberOfMates = 10;

	for (start = 0, sum = 0; sum < this->robby__.size(); ++start) {
		
		int j, babies;
		for (j = 0, babies = 16; j < numberOfMates; ++j) {
			pairs.push_back(pairer());
			pairs.back().firstIndex = start;
			pairs.back().secondIndex = start + j + 1;
			pairs.back().numberOfBabies = babies;
			//std::cout << (*pairIt).firstIndex << ' ' << (*pairIt).secondIndex << std::endl;
			// -1000, 500 -> range = 1500 -> % = (score+1000)/1500 for each robot -> pair % = {(score+1000)/1500}^2, scores may actually be differnt
			// make all relavtive scores positive to avoid weird results
	//		(*pairIt).percent = (double)((this->robby__[(*pairIt).firstIndex].getScore()+1000.0)*(this->robby__[(*pairIt).secondIndex].getScore()+1000.0))/2250000.0;
			//std::cout << (*pairIt).percent << std::endl;
			sum += babies;

			if (babies != 2) {
				babies /= 2;
			}
		}

		if (numberOfMates != 1) {
			--numberOfMates;
		}
	}

	// order in decending order by percentage of pair
	//std::sort(pairs.begin(),pairs.end(),compPercent);

//	std::vector<pairer>::iterator ilk;

//	for(ilk = pairs.begin(); ilk != pairs.end(); ++ilk)	{
//		std::cout << (*ilk).percent << ' ';
//	}

	std::vector<Robot> tmp(this->robby__.size(),Robot());
	std::vector<Robot>::iterator tmpIt;
//	std::vector<int>::iterator algIt;
	std::vector<int> newAlg(this->robby__[0].getAlgorithm().size());
	std::vector<int> alg1;
	std::vector<int> alg2;
	int choose;
	int babies;
	//int counter;
	//int babies;
	std::vector<pairer>::iterator pairIt;

	for(pairIt = pairs.begin(); pairIt < pairs.end(); ++pairIt)	{
	//	if(counter < 20)	{
	//		babies = 4;
	//	}
	//	else	{
	//		babies = 2;
	//	}

		for (tmpIt = tmp.begin(), babies = pairIt->numberOfBabies; babies > 0, tmpIt < tmp.end(); --babies, ++tmpIt) {
			alg1 = this->robby__[pairIt->firstIndex].getAlgorithm();
			alg2 = this->robby__[pairIt->secondIndex].getAlgorithm();
			int i;

			for(i = 0; i < newAlg.size(); ++i)	{
				choose = rand() % 100 + 1;	// random number between 1 and 100

				// mutate at rate of 2%
				if(choose > 50)	{
					newAlg[i] = alg1[i];	// mom's gene
				}
				else if(choose > 2)	{
					newAlg[i] = alg2[i];	// dad's gene
				}
				else	{
					newAlg[i] = rand() % 6;	// mutated gene is random
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