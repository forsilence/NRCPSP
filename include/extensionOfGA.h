# if ! defined(_EXTENIONOFGA_H)
# define _EXTENIONOFGA_H
# include"_GeneticAlgorithm.h"
namespace _HeuristicAlgorithm
{
class stableGA : public GeneticAlgorithm{
  public:
  stableGA():GeneticAlgorithm(){
    name = "stable-GA";
  }
  stableGA(const int popSize_):GeneticAlgorithm(popSize_){
    name = "stable-GA";
  }
  stableGA(const int popSize_,const int maxGeneration_,const double mutateP_):GeneticAlgorithm(popSize_,maxGeneration_, mutateP_){
    name = "stable-GA";
  }
  virtual void run() override;
  std::vector<int> selectParents_stable(const population_t& pop);
};

/**
 * 种群多样性
 * 在一代代的反复重组的种群中，常常会导致均一性,它意味着整个种群变成了一个克隆的种群。
 * 均一性限制了进化算法对搜索空间的深入探索。
 * 尽管进化算法收敛到的候选解通常是一个好的解，但是，在搜索空间的其他区域中可能还存在更好的解；
 * 因此，即使在进化算法找到是一个好的解子厚之后，我们仍然希望它能继续尝试找到更好的解是。
 * 在找到优化问题的一个令人满意的解之前就出现均一性，这种现象被称为过早收敛是。
 * 为了防止过早收敛，常用的方法持续搜索种群中的重复个体并替换它们。
 */
class diversityGA: public GeneticAlgorithm{
  public:
  diversityGA():GeneticAlgorithm(){
    name = "diversity-GA";
  }
  diversityGA(const int popSize_):GeneticAlgorithm(popSize_){
    name = "diversity-GA";
  }
  diversityGA(const int popSize_,const int maxGeneration_,const double mutateP_):GeneticAlgorithm(popSize_,maxGeneration_, mutateP_){
    name = "diversity-GA";
  }
  virtual void run() override;
};

}// _HeuristicAlgorithm
# endif