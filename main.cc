// resource-constrained project scheduling problem
# include<iostream>
# include<string>
# include<ctime>
# include"include/_GeneticAlgorithm.h"
# include"include/_GeneticAlgorithmTest.h"
# include"include/extensionOfGA.h"
// # include"include/_TemplateTest.h"
# include"include/controller.hpp"

int main(int argc, char *argv[])
{
	_HeuristicAlgorithm::AlgorithmsControl::GeneticAlgorithmController gaController;
	gaController(argc,argv);
	return 0;
}
	// std::cout << ">>> resource-constrained project scheduling problem <<<" << std::endl;
	// bool build_exe_file = true;
	// if(!build_exe_file){
	// 	_HeuristicAlgorithm::Test::TemplateTest tt;
	// 	tt.run_test();
	// }else{
	// 	_HeuristicAlgorithm::diversityGA GA;
	// 	std::string loadfile;
	// 	std::string logfile;
	// 	int maxG = 200;
	// 	int popsize = 20;
	// 	if(argc>1){
	// 		loadfile = argv[1];
	// 		if(argc>2){
	// 			logfile = argv[2];
	// 			if (logfile=="x"){
	// 				logfile = "";
	// 			}else if (logfile == "d"){
					// // find last "/" or "\"
					// int location = loadfile.size();
					// for (; location > 0; --location){
					// 	if (loadfile[location] == '\\' || loadfile[location] == '/'){
					// 		break;
					// 	}
					// }
					// if (loadfile[location] == '\\' || loadfile[location] == '/'){
					// 	logfile = loadfile;
					// 	logfile.insert(location,".rs").replace(logfile.size() - 2, 2,"cs").append("v");
					// }
	// 			}
	// 			if(argc>3){
	// 				maxG = std::atoi(argv[3]);
	// 				if(maxG<0){
	// 					std::cout << "maxG must be > 0" << std::endl;
	// 					goto label;
	// 				}
	// 				if(argc>4){
	// 					popsize = std::atoi(argv[4]);
	// 					if(maxG<0){
	// 						std::cout << "popsize must be > 0" << std::endl;
	// 						goto label;
	// 					}
	// 					if(argc>5){
	// 						double mutateP = std::atof(argv[5]);
	// 						if(mutateP<0){
	// 							std::cout << "mutateP must be > 0" << std::endl;
	// 							goto label;
	// 						}
	// 						GA.setMutateP(mutateP);
	// 						if(argc>6){
	// 							double crossoverP = std::atof(argv[6]);
	// 							if(crossoverP<0){
	// 								std::cout << "crossoverP must be > 0" << std::endl;
	// 								goto label;
	// 							}
	// 							GA.setCrossoverP(crossoverP);
	// 						}
	// 					}
	// 				}
	// 			}
	// 		} 
	// 		GA.setLoadFile(loadfile);
	// 		GA.setLogWriterPath(logfile);
	// 		GA.setMaxGeneration(maxG);
	// 		GA.setPopSize(popsize);
	// 		GA.run();
	// 	}else{
	// 	label:
	// 		std::cout << "params : loadfile logfile(x for empty, d for default output file) maxG popsize mutateP crossoverP " << std::endl;
	// 	}
	// }