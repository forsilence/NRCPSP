// resource-constrained project scheduling problem
# include<iostream>
# include<string>
# include<ctime>
# include"include/_GeneticAlgorithm.h"

int main()
{
	std::cout << ">>> resource-constrained project scheduling problem <<<" << std::endl;
	int popSize = 10;
	int maxGeneration = 20;
	double mutateP = 0.01;
	_HeuristicAlgorithm::GeneticAlgorithm ga(popSize,maxGeneration,mutateP);
	ga.setLoadFile("data/j30.sm/j301_1.sm");
	ga.setLogWriterPath("data/j30.sm.rs/j301_1.sm");
	ga.run();
	return 0;
}