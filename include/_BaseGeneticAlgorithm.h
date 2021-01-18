# if ! defined(_BASEGENETICALGORITHM_H)
# define _BASEGENETICALGORITHM_H
# include"_HeuristicAlgorithm.h"
# include<vector>
# include<map>
namespace _HeuristicAlgorithm
{
class BaseGeneticAlgorithm: public HeuristicAlgorithmBase
{
public:
BaseGeneticAlgorithm();
BaseGeneticAlgorithm(const int popSize_);
BaseGeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_);
BaseGeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_,const double crossoverP_);

void setPopSize(int const popSize_);
void setMaxGeneration(int const maxGeneration_);
void setMutateP(double const mutateP_);
void setCrossoverP(double const crossoverP_);
int getPopSize() const ;
int getMaxGeneration() const ;
double getMutateP() const ;
double getCrossoverP() const ;

void setLoadFile(std::string dataPath);
void setLogFile(std::string LogFilePath);
protected:
int popSize;
int maxGeneration;
double mutateP;
double crossoverP;
std::string dataFilePath;
};
}// _HeuristicAlgorithm
# endif