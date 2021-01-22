# include<string>
# include"../include/_GeneticAlgorithmTest.h"
# include"../include/_GeneticAlgorithm.h"
namespace _HeuristicAlgorithm
{
namespace Test
{
void GAScheduleTest ::run_test(){
  GeneticAlgorithm Ga;
  Ga.setLoadFile("./data/j30.sm/j301_2.sm");
  Ga.load("./data/j30.sm/j301_2.sm");
  Ga.setLogWriterPath("./data/j30.sm.rs/j301_2.sm.csv");
  chromosome ind(32);
  for(int i=0;i<ind.size();++i){
    ind[i]=Ga.Uniform(0,9);
  }
  auto topological_ = Ga.topological_sort(ind);
  auto all_scheduled_res = Ga.evaluate(topological_,ind);
  for(auto it:all_scheduled_res){
    Ga.logWriteIn(it.second.date_format());
  }
}

void GAInitPopTest::run_test(){
  GeneticAlgorithm Ga;
  Ga.setLoadFile("./data/j30.sm/j301_2.sm");
  Ga.load("./data/j30.sm/j301_2.sm");
  Ga.setLogWriterPath("./data/j30.sm.rs/j301_2.sm.csv");
  chromosome ind(32);
  for(int i=0;i<ind.size();++i){
    ind[i]=Ga.Uniform(0,9);
  }
  Ga.initPop(100,122);
}
} // namespace Test

} // namespace _HeuristicAlgorithm