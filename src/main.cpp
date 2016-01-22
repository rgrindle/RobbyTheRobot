#include "RobotRuler.hpp"
#include <iostream>
#include <fstream>

int main()
{
	//EnvironementCreator robbyWorld(10,10);
	//robbyWorld.setState(1,.33);

	//std::cout << robbyWorld << std::endl;
	RobotRuler god(100,10,11);

	//std::cout << god << std::endl;


	//std::cout << "Score " << god.getScore(0) << std::endl;
	std::cout << god << std::endl;
	//god.saveAlgorithmList();

	std::ofstream out("./data_test.txt");
	int i;

	for(i = 0; i < 10; ++i)	{
		out << "Generation," << "Minimum," << "Average," << "Maximum," << std::endl;
		god.simulateGeneration(200,100);
		god.rankRobots();
		god.mate();
	}
	out.close();

	return 0;
}
