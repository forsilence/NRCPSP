# include"../include/_BaseGeneticAlgorithm.h"
# include<ctime>
# include<vector>
namespace _HeuristicAlgorithm
{
// constructors
BaseGeneticAlgorithm::BaseGeneticAlgorithm():popSize(10),maxGeneration(40),mutateP(0.01),crossoverP(0.8){}
BaseGeneticAlgorithm::BaseGeneticAlgorithm(const int popSize_):BaseGeneticAlgorithm()
{
	popSize = popSize_;
}
BaseGeneticAlgorithm::BaseGeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_):
                                popSize(popSize_),maxGeneration(maxGeneration_),mutateP(mutateP_){}
BaseGeneticAlgorithm::BaseGeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_,const double crossoverP_):
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