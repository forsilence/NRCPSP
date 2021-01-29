# include"../include/extensionOfGA.h"
# include<ctime>
# include"../include/_M_processing_line.h"
namespace _HeuristicAlgorithm
{
// stable GA
// in book 进化优化算法--基于仿生和种群的计算机智能方法 P153
// it talk about stability that death and birth happens at the same time
// so this version was trying to accomplish this kind of stability
void stableGA::run(){
	std::cout << ">>> GeneticAlgorithm <<<" << std::endl;
	// record time
	time_t t = clock();
	unsigned random_seed = InitRandomSeed();
	load(dataFilePath);
	logWriteIn("rand-seed "+std::to_string(random_seed));
	logWriteIn("gsize "+std::to_string(maxGeneration));
	logWriteIn("popsize "+std::to_string(popSize));
	logWriteIn("cp "+std::to_string(crossoverP));
	logWriteIn("mp "+std::to_string(mutateP));
	auto all_jobs_ = get_all_jobs_map();
	best_res.setVal(INT_MAX);
	auto allJobs = get_all_jobs_map();
	// init pop
	std::vector<chromosome> pop = initPop(popSize,allJobs.size());
  int size_for_one_generation = 6; // "代沟" in book
  for(int generation=0 ; generation<maxGeneration; ++generation){
		print_line(generation+1,maxGeneration);
    for(int inGenerationLoop=0 ; inGenerationLoop<size_for_one_generation/2 ; ++inGenerationLoop){
      std::vector<int> selectedParents = selectParents(pop);
      auto children = crossover(population_t{pop[selectedParents[0]],pop[selectedParents[1]]});
      for(int child=0 ; child<children.size() ; ++child){
        mutate(children[child],mutateP);
        double child_schedule_res = schedule(children[child]);
        children[child].setVal(child_schedule_res);
        if(chromosome::cmp(children[child],best_res)){
          best_res = children[child];
          logWriteIn(std::to_string(best_res.getVal()));
        }
        if(chromosome::cmp(child,pop[selectedParents[child]])){
          pop[selectedParents[child]] = children[child];
        }
      }
    }
  }
  logWriteIn("runtime "+std::to_string((clock()-t)/CLOCKS_PER_SEC));
}

std::vector<int> stableGA::selectParents(population_t& pop){
	double sum = 0;
	for(const population_t::value_type& it:pop){
		sum += it.getVal();
	}
	double random_val_for_p1 = Uniform(0,1);
	double random_val_for_p2 = random_val_for_p1;
	while(random_val_for_p1 == random_val_for_p2) {
		random_val_for_p2 = Uniform(0,1);
	}
	std::vector<double> probability_inds(pop.size());
	for(int ind=0 ; ind<pop.size(); ++ind){
		probability_inds[ind] = pop[ind].getVal()/sum ;
	}
	std::vector<int> selected_parents;
	sum = 0;
	for(int ind=0 ; ind<pop.size(); ++ind){
		if(random_val_for_p1>sum && random_val_for_p1<sum+probability_inds[ind]){
			selected_parents.push_back(ind);
		}
		if(random_val_for_p2>sum && random_val_for_p2<sum+probability_inds[ind]){
			selected_parents.push_back(ind);
		}
		sum += probability_inds[ind];
	}
	int count = 2 - selected_parents.size();
	while(count){
		selected_parents.push_back(pop.size()-count);
		--count;
	}
	return selected_parents;
}
}// _HeuristicAlgorithm