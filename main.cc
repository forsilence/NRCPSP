// resource-constrained project scheduling problem
# include<iostream>
# include<string>
# include<ctime>
# include"include/_GeneticAlgorithm.h"
# include"include/_GeneticAlgorithmTest.h"

int main(int argc, char *argv[])
{
	std::cout << ">>> resource-constrained project scheduling problem <<<" << std::endl;
	_HeuristicAlgorithm::GeneticAlgorithm GA;
	std::string loadfile;
	std::string logfile;
	int maxG = 100;
	int popsize = 20;
	if(argc>1){
		loadfile = argv[1];
		if(argc>2){
			logfile = argv[2];
			if (logfile=="x"){
				logfile = "";
			}
			if(argc>3){
				maxG = std::atoi(argv[3]);
				if(maxG<0){
					std::cout << "maxG must be > 0" << std::endl;
				}
				if(argc>4){
					popsize = std::atoi(argv[4]);
					if(maxG<0){
						std::cout << "popsize must be > 0" << std::endl;
					}
				}
			}
		}
		GA.setLoadFile(loadfile);
		GA.setLogWriterPath(logfile);
		GA.setMaxGeneration(maxG);
		GA.setPopSize(popsize);
		GA.run();
	}else{
		std::cout << "params : loadfile logfile(x for empty) maxG popsize mutateP crossoverP " << std::endl;
	}
	return 0;
}