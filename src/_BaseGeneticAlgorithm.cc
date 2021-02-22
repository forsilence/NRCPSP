# include"../include/_BaseGeneticAlgorithm.h"
# include<ctime>
# include<vector>
namespace _HeuristicAlgorithm
{
// constructors
BaseGeneticAlgorithm::BaseGeneticAlgorithm(std::string name_):HeuristicAlgorithmBase(name_),popSize(10),maxGeneration(40),mutateP(0.01),crossoverP(0.8){}
BaseGeneticAlgorithm::BaseGeneticAlgorithm(std::string name_,const int popSize_):BaseGeneticAlgorithm(name_)
{
	popSize = popSize_;
}
BaseGeneticAlgorithm::BaseGeneticAlgorithm(std::string name_, const int popSize_,const int maxGeneration_,const double mutateP_):HeuristicAlgorithmBase(name_),
                                popSize(popSize_),maxGeneration(maxGeneration_),mutateP(mutateP_){}
BaseGeneticAlgorithm::BaseGeneticAlgorithm(std::string name_,const int popSize_,const int maxGeneration_,const double mutateP_,const double crossoverP_):HeuristicAlgorithmBase(name_),
                                popSize(popSize_),maxGeneration(maxGeneration_),mutateP(mutateP_),crossoverP(crossoverP_){}
// >>>set params for genetic algorithm<<<
// set
void BaseGeneticAlgorithm::setPopSize(int const popSize_)
{
	this->popSize = popSize_;
}
void BaseGeneticAlgorithm::setMaxGeneration(int const maxGeneration_)
{
	this->maxGeneration = maxGeneration_;
}
void BaseGeneticAlgorithm::setMutateP(double const mutateP_)
{
	this->mutateP = mutateP_;
}
void BaseGeneticAlgorithm::setCrossoverP(double const crossoverP_)
{
	this->crossoverP = crossoverP_;
}
// get
int BaseGeneticAlgorithm::getPopSize() const 
{
	return popSize;
}
int BaseGeneticAlgorithm::getMaxGeneration() const 
{
	return maxGeneration;
}
double BaseGeneticAlgorithm::getMutateP() const 
{
	return mutateP;
}
double BaseGeneticAlgorithm::getCrossoverP() const
{
	return crossoverP;
}
// set load file 
void BaseGeneticAlgorithm::setLoadFile(std::string dataPath)
{
	dataFilePath = dataPath;
}
}// _HeuristicAlgorithm