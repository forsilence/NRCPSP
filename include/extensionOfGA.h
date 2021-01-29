# if ! defined(_EXTENIONOFGA_H)
# define _EXTENSIONOFGA_H
# include"_GeneticAlgorithm.h"
namespace _HeuristicAlgorithm
{
class stableGA : public GeneticAlgorithm{
  public:
  virtual void run() override;
  virtual std::vector<int> selectParents(population_t& pop);
};
}// _HeuristicAlgorithm
# endif