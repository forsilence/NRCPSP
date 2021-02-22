#include "../include/controller.hpp"
namespace _HeuristicAlgorithm
{
namespace AlgorithmsControl{
AlgorithmsGetter::AlgorithmsGetter()
{
  GAMap = {{AlgorithmsType::def,new GeneticAlgorithm}, {AlgorithmsType::diversityGeneticA, new diversityGA} , {AlgorithmsType::stableGeneticA,new stableGA}};
}

BaseGeneticAlgorithm* AlgorithmsGetter::GetAlgorithm(AlgorithmsType at_)
{
  return GAMap.find(at_)->second;
}

void AlgorithmsController::setArgs(int argc,char* argv[])
{
  std::string key;
  for ( int arg = 1; arg < argc; ++arg){
    if (argv[arg][0] == '-') {
      key = argv[arg];
      args_map.emplace(key,std::vector<std::string>());
    }else{
      args_map.find(key)->second.push_back(argv[arg]);
    }
  }
}
void GeneticAlgorithmController::setGA(BaseGeneticAlgorithm* ga_)
{
  ga = ga_;
}

void GeneticAlgorithmController::operator()(int argc, char* argv[])
{
  setArgs(argc,argv);
  // get format : 
  if (args_map.find("-format") != args_map.end()){
    std::cout << "main [-A algorithmstype] -I InputFile [-O Outout] [-G maxGeneration] [-P popsize] [-M mutatep] [-C crossoverP]" << std::endl;
    exit(0);
  }
  // handle ga : default , diversity, stable
  auto arg_atype = args_map.find("-A");
  if (arg_atype == args_map.end()){
    setGA(algorithmsgetter.GetAlgorithm(AlgorithmsGetter::AlgorithmsType::def));
  }else{
    if (arg_atype->second[0] == "diversity"){
      setGA(algorithmsgetter.GetAlgorithm(AlgorithmsGetter::AlgorithmsType::diversityGeneticA));
    }else if (arg_atype->second[0] == "stable"){
      setGA(algorithmsgetter.GetAlgorithm(AlgorithmsGetter::AlgorithmsType::stableGeneticA));
      // ga->run();
    }else{
      std::cout << "Unknown Gatype" << std::endl;
      exit(1);
    }
  }
  // handle input file
  auto arg_input = args_map.find("-I");
  if (arg_input == args_map.end()){
    std::cout << "No input file : you should add -I input_file" << std::endl;
    exit(1);
  }
  ga->setLoadFile(arg_input->second[0]);
  // handle output file
  std::string logfile;
  auto arg_output = args_map.find("-O");
  if (arg_output != args_map.end()) {
    // d for default out file
    if ( arg_output->second[0] == "d") {
      // find last "/" or "\"
      std::string loadfile = arg_input->second[0];
      int location = loadfile.size();
      for (; location > 0; --location){
        if (loadfile[location] == '\\' || loadfile[location] == '/'){
          break;
        }
      }
      if (loadfile[location] == '\\' || loadfile[location] == '/'){
        logfile = loadfile;
        logfile.insert(location,".rs").replace(logfile.size() - 2, 2,"cs").append("v");
      }
    }else{
      logfile = arg_output->second[0];
    }
    ga->setLogWriterPath(logfile);
  } 
  // max generation
  int maxG = 40;
  if (args_map.find("-G") != args_map.end()){
    maxG = std::atoi(args_map.find("-G")->second[0].c_str());
  }
  ga->setMaxGeneration(maxG);
  // pop size
  int popsize = 20;
  if (args_map.find("-P") != args_map.end()) {
    popsize = std::atoi(args_map.find("-P")->second[0].c_str());
  }
  ga->setPopSize(popsize);
  // mutate p
  double mutateP = 0.02;
  if (args_map.find("-M") != args_map.end()) {
    mutateP = std::atoi(args_map.find("-M")->second[0].c_str());
  }
  ga->setMutateP(mutateP);
  // crossover p
  double crossoverP = 0.5;
  if (args_map.find("-C") != args_map.end()) {
    crossoverP = std::atoi(args_map.find("-C")->second[0].c_str());
  }
  ga->setCrossoverP(crossoverP);
  ga->run();
  ga->into_file();
}
} // AlgorithmsControl
} // _HeuristicAlgorithm