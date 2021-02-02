# include"../include/_TemplateTest.h"
# include"../include/_GeneticAlgorithm.h"
# include"../include/_Template_GA.h"
namespace _HeuristicAlgorithm
{
namespace Test
{
void TemplateTest::run_test() {
  logWriteIn(">>> Template Test <<<");
  Template::RepeatIn<GeneticAlgorithm::population_t,GeneticAlgorithm::population_t::value_type> repeatIn;
  GeneticAlgorithm GA;
  GA.setLoadFile("./data/j30.sm/j301_1.sm");
  GA.load("./data/j30.sm/j301_1.sm");
  auto pop = GA.initPop(11,32);
  // 打印种群
  for(auto& ind:pop){
    for(int i=0 ; i<ind.size(); ++i){
      std::cout << ind[i] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "-" << std::endl;
  // 提取第一个个体
  auto alone = pop[pop.size()-1];
  // 检查是否在
  if(repeatIn(pop,alone)){
    std::cout << "in it" << std::endl;
  }else{
    std::cout << "not in" << std::endl;
  }
  std::cout << "pop last one" << std::endl;
  // 去掉最后一个
  pop.pop_back();
  // 检查是否在
  if(repeatIn(pop,alone)){
    std::cout << "in it" << std::endl;
  }else{
    std::cout << "not in" << std::endl;
  }
}
} // Test
} // _HeuristicAlgorithm