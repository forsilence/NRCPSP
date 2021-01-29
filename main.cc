// resource-constrained project scheduling problem
# include<iostream>
# include<string>
# include<ctime>
# include"include/_GeneticAlgorithm.h"
# include"include/_GeneticAlgorithmTest.h"
# include"include/extensionOfGA.h"

int main(int argc, char *argv[])
{
	std::cout << ">>> resource-constrained project scheduling problem <<<" << std::endl;
	_HeuristicAlgorithm::GeneticAlgorithm GA;
	std::string loadfile;
	std::string logfile;
	int maxG = 200;
	int popsize = 20;
	// GA.setLogWriterPath("./data/j30.sm.rs/j303_3.csv");
	// GA.setLoadFile("./data/j30.sm/j303_3.sm");
	// GA.setMaxGeneration(maxG);
	// GA.setPopSize(popsize);
	// GA.run();
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
					goto label;
				}
				if(argc>4){
					popsize = std::atoi(argv[4]);
					if(maxG<0){
						std::cout << "popsize must be > 0" << std::endl;
						goto label;
					}
					if(argc>5){
						double mutateP = std::atof(argv[5]);
						if(mutateP<0){
							std::cout << "mutateP must be > 0" << std::endl;
							goto label;
						}
						GA.setMutateP(mutateP);
						if(argc>6){
							double crossoverP = std::atof(argv[6]);
							if(crossoverP<0){
								std::cout << "crossoverP must be > 0" << std::endl;
								goto label;
							}
							GA.setCrossoverP(crossoverP);
						}
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
	label:
		std::cout << "params : loadfile logfile(x for empty) maxG popsize mutateP crossoverP " << std::endl;
	}
	return 0;
}