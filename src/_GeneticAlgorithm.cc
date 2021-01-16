# include"../include/_GeneticAlgorithm.h"
# include<ctime>
# include<vector>
# include<iostream>
namespace _HeuristicAlgorithm
{
void GeneticAlgorithm::run()
{
	std::cout << ">>> GeneticAlgorithm <<<" << std::endl;
	load(dataFilePath);
	auto all_jobs_ = get_all_jobs_map();
	for (auto job:all_jobs_){
		logWriteIn(job.second.toString());
	}
	auto allJobs = get_all_jobs_map();
	// init pop
	std::vector<chromosome> pop = initPop(popSize);
	for(int Generationloop=0; Generationloop<maxGeneration;++Generationloop){
		population_t newGeneration;
		for(int inGenerationLoop=0;inGenerationLoop<popSize*crossoverP;++inGenerationLoop){
			population_t selectedParents = selectParents(pop);
			population_t children = crossover(selectedParents);
			for(int child=0;child<children.size();++child){
				mutate(children[child], mutateP);
				// push child to newGeneration
				newGeneration.push_back(children[child]);
			}
		}
		pop = popSort(pop);
		for(int delLoop=0 ; delLoop < pop.size() - popSize ; ++delLoop){
			pop.erase(pop.begin());
		}
	}
}
// need to finish
double GeneticAlgorithm::schedule(chromosome ind)
{
	std::vector<_DataLoad::job::number_t> ts = topological_sort(ind);

	return 0;
}
std::vector<_DataLoad::job::number_t> GeneticAlgorithm::topological_sort(chromosome ind)
{
	// init
	no_job_t free_activities = get_all_jobs_map();
	no_job_t sorted_activities;
	std::vector<_DataLoad::job::number_t> schedule_order;

	// push the activities 0 to sorted activities and remove from free_activities
	no_job_t::iterator deleter_for_free_activities = free_activities.find(0);
	sorted_activities.emplace(deleter_for_free_activities->first,
															deleter_for_free_activities->second);
	schedule_order.push_back(deleter_for_free_activities->first);
	
	// init priority queue
	no_job_t priority_queue;

	for(_DataLoad::job::number_t it:deleter_for_free_activities->second.get_successors()){
		no_job_t::iterator deleter_for_sucessors = free_activities.find(it);
		priority_queue.emplace(deleter_for_free_activities->first,
														deleter_for_free_activities->second);
		free_activities.erase(deleter_for_sucessors);
	}
	// remove 0 activities from free activities
	free_activities.erase(deleter_for_free_activities);

	// init cut set
	cut_set_t cut_set;
	update_cut_set(sorted_activities,cut_set,0);
	while(sorted_activities.size() != ind.size()){
		deleter_for_free_activities = max_priority(priority_queue,ind);
		if(deleter_for_free_activities!=priority_queue.end()){
				sorted_activities.emplace(deleter_for_free_activities->first,
														deleter_for_free_activities->second);
				schedule_order.push_back(deleter_for_free_activities->first);
				priority_queue.erase(deleter_for_free_activities);
		}
		update_cut_set(priority_queue,
										cut_set,
										deleter_for_free_activities->first);
		std::size_t cut_set_size = cut_set.size();
		update_priority_activities( sorted_activities,
																cut_set,
																free_activities,
																priority_queue);
	}
	return schedule_order;
}

void GeneticAlgorithm::update_cut_set( const no_job_t& sorted_activities,
                                        cut_set_t& cut_set,
                                        _DataLoad::job::number_t job_no)
{
	std::vector<_DataLoad::job::number_t> predecessors = sorted_activities.at(job_no).get_predecessors();
	std::vector<_DataLoad::job::number_t> successors   = sorted_activities.at(job_no).get_successors();
	cut_set_t::iterator delete_iter;
	// delete cut_set element that not exist!
	for( int pre=0 ; pre<predecessors.size() ; pre++ ){
		delete_iter = cut_set.find(predecessors[pre]);
		if (delete_iter != cut_set.end()){
				cut_set.erase(delete_iter);
		}
	}
	// add new element to cut_set
	for(int suc=0 ; suc<successors.size() ; suc++ ){
		cut_set.emplace(job_no,successors[suc]);
	}
}

GeneticAlgorithm::no_job_t::iterator GeneticAlgorithm::max_priority( 
    no_job_t& pr_queue, 
    const chromosome& gene)
{
	no_job_t::iterator max_job = pr_queue.begin();
	for(auto it=max_job;it!=pr_queue.end();++it){
		if(gene[it->first]>gene[max_job->first]){
			max_job=it;
		}
	}
	return max_job;
}

void GeneticAlgorithm::update_priority_activities(  const no_job_t& sorted_activities,
                                                    const cut_set_t& cut_set,
                                                    no_job_t& free_activities,
                                                    no_job_t& priority_queue)
{
	for(cut_set_t::value_type it:cut_set){
		no_job_t::iterator job_iterator = free_activities.find(it.second);
		if( job_iterator != free_activities.end()){
			if(eligible(sorted_activities,job_iterator->second)){
				priority_queue.emplace(job_iterator->first,job_iterator->second);
				free_activities.erase(job_iterator);
			}
		}
	}
}

bool GeneticAlgorithm::eligible(const no_job_t& sorted_activities,const _DataLoad::job& j)
{
	for( _DataLoad::job::number_t pre:j.get_predecessors()){
		if(sorted_activities.find(pre) == sorted_activities.end()){
			return false;
		}
	}
	return true;
}

// need to finish
GeneticAlgorithm::no_job_t GeneticAlgorithm::evaluate(  std::vector<_DataLoad::job::number_t> topological_sort_res,
                                                        const chromosome& gene)
{
	no_job_t all_jobs = get_all_jobs_map();
	_DataLoad::job::resource_bulk_t limited_resources = get_resources();
}

// >>>chromosome<<<
int& chromosome::operator[](size_t location)
{
	return MChromosome[location];
}
int chromosome::operator[](size_t location) const {
	return MChromosome[location];
}
std::size_t chromosome::size()const {
	return this->MChromosome.size();
}
}// _HeuristicAlgorithm