## resource-constrained project scheduling problem
 new project for RCPSP
 compare to RCPSP ,this project run faster and provide more basic operations for further algorithms
#### class introduction
* _DataLoad::infor_loader
> load data
* HeuristicAlgorithmBase
> provide basic operation for all kind of heuristic algorithm(log_write , uniform_distribution)
* BaseGeneticAlgorithm
> provide basic operation for all the Genetic algorithm (population_size , crossover_probability , mutate_probability)
* GeneticAlgorithm
> an implementation of genetic algorithm
> using example
```c++
_HeuristicAlgorithm::GeneticAlgorithm GA;
GA.setLoadFile(loadfile);
GA.setLogWriterPath(logfile);
GA.setMaxGeneration(maxG);
GA.setPopSize(popsize);
GA.run();
```