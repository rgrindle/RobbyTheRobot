#include "RobotRuler.hpp"
#include <iostream>
#include <fstream>

int main()
{
	//std::vector<int> myInts;

	//myInts.push_back(309);
	//myInts.push_back(3);
	//myInts.push_back(-323);
	//myInts.push_back(189);

	//std::vector<int>::iterator it = myInts.begin();
	//for (; it < myInts.end(); ++it) {
	//	std::cout << *it << ", ";
	//}
	//std::cout << std::endl;

	//std::sort(myInts.begin(), myInts.end());

	//for (it = myInts.begin(); it < myInts.end(); ++it) {
	//	std::cout << *it << ", ";
	//}

	//system("pause");

	///--------------------------------------- Real stuff below this line-------------------------------------///

	//EnvironementCreator robbyWorld(10,10);
	//robbyWorld.setState(1,.33);

	//std::cout << robbyWorld << std::endl;
	RobotRuler god(100,10,11);
	//RobotRuler god(100, 10, 11, "./data/algorithm/", "score_data");

	//std::cout << god << std::endl;

	//std::cout << "Score " << god.getScore(0) << std::endl;
	std::cout << god << std::endl;
	//god.saveAlgorithmList();
	//god.scoreOut << "Generation," << "Minimum," << "Average," << "Median," << "Maximum,";
	//std::ofstream out("./data_test.txt");
	int i;

	for(i = 0; i < 10000; ++i)	{
		//std::cout << "Generation " << (i + 1) << '\t';
		//god.scoreOut << std::endl << (i + 1) << ',';
		god.simulateGeneration(200,100);	// 200 moves for each of the 100 seasons
		god.rankRobots();
		god.printScore();
		god.saveAlgorithmList();
		god.mate();
	}
	//out.close();

	return 0;
}
