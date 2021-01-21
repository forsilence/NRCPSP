# include"../include/_GeneticAlgorithmTest.h"
# include<string>
# include"../include/_GeneticAlgorithmTest.h"
# include"../include/_GeneticAlgorithm.h"
namespace _HeuristicAlgorithm
{
namespace Test
{
void GAScheduleTest::run_test(){
  GeneticAlgorithm Ga;
  Ga.setLoadFile("../data/j30.sm/j301_1.sm");
  Ga.load("./data/j30.sm/j301_1.sm");
  Ga.run();
  chromosome ind(32);
  for(int i=0;i<ind.size();++i){
    ind[i]=Ga.Uniform(0,9);
  }
for (auto it:Ga.topological_sort(ind)){
  std::cout << it << " ";
}
std::cout << std::endl;
  std::cout << Ga.schedule(ind) << std::endl;;
}
} // namespace Test

} // namespace _HeuristicAlgorithm