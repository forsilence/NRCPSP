# include"../include/_GeneticAlgorithm.h"
# include<ctime>
namespace _HeuristicAlgorithm
{
void GeneticAlgorithm::run()
{
    std::cout << ">>> GeneticAlgorithm <<<" << std::endl;
    load(dataFilePath);
    auto all_jobs_ = get_all_jobs_map();
    for (auto job:all_jobs_){
        logWriteIn(job.second.toString());
    }
    auto allJobs = get_all_jobs_map();
    // init pop
    std::vector<chromosome> pop = initPop(popSize);
    for(int Generationloop=0; Generationloop<maxGeneration;++Generationloop){
        population_t newGeneration;
        for(int inGenerationLoop=0;inGenerationLoop<popSize*crossoverP;++inGenerationLoop){
            population_t selectedParents = selectParents(pop);
            population_t children = crossover(selectedParents);
            for(int child=0;child<children.size();++child){
                mutate(children[child], mutateP);
                // push child to newGeneration
                newGeneration.push_back(children[child]);
            }
        }
        pop = popSort(pop);
        for(int delLoop=0 ; delLoop < pop.size() - popSize ; ++delLoop){
            pop.erase(pop.begin());
        }
    }
}
double GeneticAlgorithm::schedule(chromosome ind)
{
}
// constructors
GeneticAlgorithm::GeneticAlgorithm():popSize(10),maxGeneration(40),mutateP(0.01),crossoverP(0.8){}
GeneticAlgorithm::GeneticAlgorithm(const int popSize_):GeneticAlgorithm()
{
    popSize = popSize_;
}
GeneticAlgorithm::GeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_):
                                popSize(popSize_),maxGeneration(maxGeneration_),mutateP(mutateP_){}
GeneticAlgorithm::GeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_,const double crossoverP_):
                                popSize(popSize_),maxGeneration(maxGeneration_),mutateP(mutateP_),crossoverP(crossoverP_){}
// >>>set params for genetic algorithm<<<
// set
void GeneticAlgorithm::setPopSize(int const popSize_)
{
    this->popSize = popSize_;
}
void GeneticAlgorithm::setMaxGeneration(int const maxGeneration_)
{
    this->maxGeneration = maxGeneration_;
}
void GeneticAlgorithm::setMutateP(double const mutateP_)
{
    this->mutateP = mutateP_;
}
void GeneticAlgorithm::setCrossoverP(double const crossoverP_)
{
    this->crossoverP = crossoverP_;
}
// get
int GeneticAlgorithm::getPopSize() const 
{
    return popSize;
}
int GeneticAlgorithm::getMaxGeneration() const 
{
    return maxGeneration;
}
double GeneticAlgorithm::getMutateP() const 
{
    return mutateP;
}
double GeneticAlgorithm::getCrossoverP() const
{
    return crossoverP;
}
// set load file 
void GeneticAlgorithm::setLoadFile(std::string dataPath)
{
    dataFilePath = dataPath;
}
// >>>chromosome<<<
int& chromosome::operator[](size_t location)
{
    return MChromosome[location];
}
}// _HeuristicAlgorithm