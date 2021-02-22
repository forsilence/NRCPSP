#ifndef __CONTROLLER_HPP
#define __CONTROLLER_HPP
#include <map>
#include "_BaseGeneticAlgorithm.h"
#include "extensionOfGA.h"

namespace _HeuristicAlgorithm
{
namespace AlgorithmsControl{
class AlgorithmsGetter{
  public:
  AlgorithmsGetter();
  enum AlgorithmsType{def, stableGeneticA, diversityGeneticA};
  BaseGeneticAlgorithm* GetAlgorithm(AlgorithmsType at_);
  private:
  std::map<AlgorithmsType,BaseGeneticAlgorithm *> GAMap; 
};

class AlgorithmsController{
  public:
  virtual void operator()(int argc, char* argv[]) = 0;
  void setArgs(int argc,char* argv[]);
  protected:
  std::map<std::string, std::vector<std::string>> args_map;
};

class GeneticAlgorithmController: public AlgorithmsController{
  public:
  GeneticAlgorithmController(BaseGeneticAlgorithm* ga_):AlgorithmsController(), ga(ga_){}
  GeneticAlgorithmController():AlgorithmsController(), ga(0){}
  void setGA(BaseGeneticAlgorithm* ga_);
  /*
  input format : main [-A algorithmstype] -I InputFile [-O Outout] [-G maxGeneration] [-P popsize] [-M mutatep] [-C crossoverP]
  */
  virtual void operator()(int argc, char* argv[]) override;
  private:
  BaseGeneticAlgorithm *ga;
  AlgorithmsGetter algorithmsgetter;
};
} // AlgorithmsControl
} // _HeuristicAlgorithm
#endif