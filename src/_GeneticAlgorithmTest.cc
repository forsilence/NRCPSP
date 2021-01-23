# include<string>
# include"../include/_GeneticAlgorithmTest.h"
# include"../include/_GeneticAlgorithm.h"
# include<ctime>
namespace _HeuristicAlgorithm
{
namespace Test
{
void GAScheduleTest ::run_test(){
  GeneticAlgorithm Ga;
  Ga.setLoadFile("./data/j30.sm/j301_1.sm");
  Ga.load("./data/j30.sm/j301_1.sm");
  Ga.setLogWriterPath("./data/j30.sm.rs/j301_12.sm.csv");
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
  time_t t = clock();
  Ga.initPop(5000,32);
  time_t take_time = clock() - t;
  std:: cout << 1000 << " inds take time is " << take_time/CLOCKS_PER_SEC << std::endl;
}

void GASelectParents::run_test(){
  GeneticAlgorithm Ga;
  std::string loadfile = "./data/j30.sm/j301_3.sm";
  Ga.setLoadFile(loadfile);
  Ga.load(loadfile);
  Ga.setLogWriterPath("./data/j30.sm.rs/j301_3.sm.csv");
  chromosome ind(32);
  for(int i=0;i<ind.size();++i){
    ind[i]=Ga.Uniform(0,9);
  }
  Ga.InitRandomSeed();
  time_t t = clock();
  std::size_t pop_size = 20;
  auto pop = Ga.initPop(pop_size,32);
  auto selected_parents = Ga.selectParents(pop);
  for(auto parent:selected_parents){
    std::string chromosome_str;
    for(int gene=0 ; gene<parent.size() ; ++gene){
      chromosome_str += std::to_string(parent[gene])+" ";
    }
    Ga.logWriteIn(chromosome_str);
    Ga.logWriteIn(std::to_string(parent.getVal()));
  }
  time_t take_time = clock() - t;
  std:: cout << pop_size << " inds take time is " << take_time/CLOCKS_PER_SEC << std::endl;
}

void GACrossoverTest::run_test(){
  GeneticAlgorithm Ga;
  std::string loadfile = "./data/j30.sm/j301_3.sm";
  Ga.setLoadFile(loadfile);
  Ga.load(loadfile);
  Ga.setLogWriterPath("./data/j30.sm.rs/j301_3.sm.csv");
  chromosome ind(32);
  for(int i=0;i<ind.size();++i){
    ind[i]=Ga.Uniform(0,9);
  }
  Ga.InitRandomSeed();
  time_t t = clock();
  std::size_t pop_size = 20;
  auto pop = Ga.initPop(pop_size,32);
  auto selected_parents = Ga.selectParents(pop);
  for(auto parent:selected_parents){
    std::string chromosome_str;
    for(int gene=0 ; gene<parent.size() ; ++gene){
      chromosome_str += std::to_string(parent[gene])+" ";
    }
    Ga.logWriteIn(chromosome_str);
    Ga.logWriteIn(std::to_string(parent.getVal()));
  }
  auto children = Ga.crossover(selected_parents);
  for(auto child:children){
    std::string chromosome_str;
    for(int gene=0 ; gene<child.size() ; ++gene){
      chromosome_str += std::to_string(child[gene])+" ";
    }
    Ga.logWriteIn(chromosome_str);
    Ga.logWriteIn(std::to_string(child.getVal()));
  }
  time_t take_time = clock() - t;
  std:: cout << pop_size << " inds take time is " << take_time/CLOCKS_PER_SEC << std::endl;
}

void GAMutateTest::run_test(){
  GeneticAlgorithm Ga;
  std::string loadfile = "./data/j30.sm/j301_3.sm";
  Ga.setLoadFile(loadfile);
  Ga.load(loadfile);
  Ga.setLogWriterPath("./data/j30.sm.rs/j301_3.sm.csv");
  chromosome ind(32);
  for(int i=0;i<ind.size();++i){
    ind[i]=Ga.Uniform(0,9);
  }
  Ga.InitRandomSeed();
  time_t t = clock();
  std::size_t pop_size = 20;
  auto pop = Ga.initPop(pop_size,32);
  auto selected_parents = Ga.selectParents(pop);
  for(auto parent:selected_parents){
    std::string chromosome_str;
    for(int gene=0 ; gene<parent.size() ; ++gene){
      chromosome_str += std::to_string(parent[gene])+" ";
    }
    Ga.logWriteIn(chromosome_str);
    Ga.logWriteIn(std::to_string(parent.getVal()));
  }
  Ga.logWriteIn("crossover");
  auto children = Ga.crossover(selected_parents);
  for(auto child:children){
    std::string chromosome_str;
    for(int gene=0 ; gene<child.size() ; ++gene){
      chromosome_str += std::to_string(child[gene])+" ";
    }
    Ga.logWriteIn(chromosome_str);
    Ga.logWriteIn(std::to_string(child.getVal()));
  }
  for(auto& child:children){
    Ga.mutate(child,Ga.getMutateP());
  }
  for(auto child:children){
    std::string chromosome_str;
    for(int gene=0 ; gene<child.size() ; ++gene){
      chromosome_str += std::to_string(child[gene])+" ";
    }
    Ga.logWriteIn(chromosome_str);
    Ga.logWriteIn(std::to_string(child.getVal()));
  }
  time_t take_time = clock() - t;
  std:: cout << pop_size << " inds take time is " << take_time/CLOCKS_PER_SEC << std::endl;
}
} // namespace Test

} // namespace _HeuristicAlgorithm