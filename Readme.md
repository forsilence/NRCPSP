## resource-constrained project scheduling problem
 new project for RCPSP  
 compare to RCPSP ,this project run faster and provide more basic operations for further algorithms  
 进化优化算法--基于仿生和种群的计算机智能方法<reference>
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
* stableGA
> in book 进化优化算法--基于仿生和种群的计算机智能方法 P153  
> it talk about stability that death and birth happens at the same time  
> so this version was trying to accomplish this kind of stability  
* diversityGA
> 种群多样性
> 在一代代的反复重组的种群中，常常会导致均一性,它意味着整个种群变成了一个克隆的种群。  
> 均一性限制了进化算法对搜索空间的深入探索。  
> 尽管进化算法收敛到的候选解通常是一个好的解，但是，在搜索空间的其他区域中可能还存在更好的解；  
> 因此，即使在进化算法找到是一个好的解子厚之后，我们仍然希望它能继续尝试找到更好的解是。  
> 在找到优化问题的一个令人满意的解之前就出现均一性，这种现象被称为过早收敛是。  
> 为了防止过早收敛，常用的方法持续搜索种群中的重复个体并替换它们。  
```c++
_HeuristicAlgorithm::GeneticAlgorithm GA;
GA.setLoadFile(loadfile);
GA.setLogWriterPath(logfile);
GA.setMaxGeneration(maxG);
GA.setPopSize(popsize);
GA.run();
```
> or in cmd(Windows)
```
NRCPSP\built_files\>GAForRCPSP-0 ../data/j60.sm/j601_2.sm ../data/j60.sm.rs/j601_2.csv 100 30
```
* rcpsp : command with some type algorithms
> use format : rcpsp -I input_file -O Output_file(d for default outputfile) -G max_generation -P pop_size -M mutate_probility -C crossover_probility  
> use example :
```
NRCPSP\built_files\>rcpsp -I ../data/j60.sm/j601_2.sm  -O ../data/j60.sm.rs/j601_2.csv -G 100 -P 30 -M 0.01 -C 0.6
```

* main : use to handle command using to handle file
> It has 4 modes now  (-S single file mode, -SM single file run multi times , -M multi files mode , -MM multi files run multi times for each )  
> -S , you should run like : main command -S file with preargs -args args  
> example : use GAForRCPSP-0  
``` 
NRCPSP\built_files\>main GAForRCPSP-0 -S ../data/j60.sm/j601_2.sm -args ../data/j60.sm.rs/j601_2.csv 100 30
```
> -SM , run format : main command -SM file with preargs -args args run_times
> example : use GAForRCPSP-0  
```
NRCPSP\built_files\>main GAForRCPSP-0 -SM ../data/j60.sm/j601_2.sm -args ../data/j60.sm.rs/j601_2.csv 100 30 4
```
> -M , run format : main command -M directory_path with preargs -args args  
> example : rcpsp
```
NRCPSP\built_files\>main rcpsp -M  -I ../data/j60.sm -args -O d  -G 100 -p 30
```
> -MM , run format : main command -MM directory_path with preargs -args args run_times  
> example : rcpsp
```
NRCPSP\built_files\>main rcpsp -MM  -I ../data/j60.sm -args -O d  -G 100 -p 30 4
```
> how to use main  
```
> main command -[mode] [preargs] path [-args args]
NRCPSP\built_files\>main rcpsp -S -I ../data/j60.sm/j601_2.sm  -args -O d -A stable  -G 100 -P 25 -M 0.01 -C 0.5
```