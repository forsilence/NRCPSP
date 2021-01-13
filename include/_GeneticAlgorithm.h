# if ! defined(_GENETICALGORITHM_H)
# define _GENETICALGORITHM_H
# include"_HeuristicAlgorithm.h"
# include<vector>
namespace _HeuristicAlgorithm
{
class chromosome;
class GeneticAlgorithm: public HeuristicAlgorithmBase
{
    public:
    typedef std::vector<chromosome> population_t;
    GeneticAlgorithm();
    GeneticAlgorithm(const int popSize_);
    GeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_);
    GeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_,const double crossoverP_);
    virtual void run() override;

    void setPopSize(int const popSize_);
    void setMaxGeneration(int const maxGeneration_);
    void setMutateP(double const mutateP_);
    void setCrossoverP(double const crossoverP_);
    int getPopSize() const ;
    int getMaxGeneration() const ;
    double getMutateP() const ;
    double getCrossoverP() const ;

    population_t initPop(size_t popSize);
    double schedule(chromosome ind);
    double objectiveFunction(chromosome ind);
    population_t selectParents(population_t pop);
    population_t crossover(population_t selectedParents);
    chromosome mutate(chromosome& ind,double mutateP);
    population_t popSort(population_t pop);

    void setLoadFile(std::string dataPath);
    void setLogFile(std::string LogFilePath);
    private:
    int popSize;
    int maxGeneration;
    double mutateP;
    double crossoverP;
    std::string dataFilePath;
};
class chromosome
{
    public:
    int& operator[](size_t location);
    void setVal(double val_);
    double getVal() const;
    private:
    std::vector<int> MChromosome;
    double val;
};
}// _HeuristicAlgorithm
# endif