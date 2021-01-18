# include"../include/_GeneticAlgorithm.h"
# include<ctime>
# include<vector>
# include<iostream>
# include<iterator>
namespace _HeuristicAlgorithm
{
GeneticAlgorithm::GeneticAlgorithm():BaseGeneticAlgorithm(){}
GeneticAlgorithm::GeneticAlgorithm(const int popSize_):BaseGeneticAlgorithm(popSize_){}
GeneticAlgorithm::GeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_):BaseGeneticAlgorithm(popSize_,maxGeneration_,mutateP_){}
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
	auto res = evaluate(ts,ind);
	return res.rbegin()->second.get_ef();
}
std::vector<_DataLoad::job::number_t> GeneticAlgorithm::topological_sort(chromosome ind)
{
	// init
	no_job_t free_activities = get_all_jobs_map();
	no_job_t sorted_activities;
	std::vector<_DataLoad::job::number_t> schedule_order;

	// push the activities 1 to sorted activities and remove from free_activities
	no_job_t::iterator deleter_for_free_activities = free_activities.find(1);
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
	update_cut_set(sorted_activities,cut_set,1);
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
GeneticAlgorithm::no_job_t GeneticAlgorithm::evaluate(  
	std::vector<_DataLoad::job::number_t> topological_sort_res,
  const chromosome& gene)
{
	no_job_t all_jobs = get_all_jobs_map();
	_DataLoad::job::resource_bulk_t limited_resources = get_resources();
	std::map<_DataLoad::job::resource_t,time_concept::time_bucket::time_line>
		time_line_for_resources;
	no_job_t scheduled_activities;
	// set time for activities 1 
	no_job_t::iterator current_activity_iterator = all_jobs.find(1);
	current_activity_iterator->second.set_es(0).set_ef(0);
	scheduled_activities.emplace(
		current_activity_iterator->first,
		current_activity_iterator->second);
	for(int activity_location=1 ; 
			activity_location<topological_sort_res.size(); 
			++activity_location){
		current_activity_iterator = all_jobs.find(topological_sort_res[activity_location]);
		set_time( current_activity_iterator->second,
							time_line_for_resources,
							scheduled_activities);
		scheduled_activities.emplace(
			current_activity_iterator->first,
			current_activity_iterator->second);
	}
	return scheduled_activities;
}

void GeneticAlgorithm::set_time(_DataLoad::job& activity,
							std::map<_DataLoad::job::resource_t,
								time_concept::time_bucket::time_line>& time_line_for_resource,
							const no_job_t& scheduled_activities)
{
	auto limited_resources = get_resources();
	// find predecessors for activity
	std::vector<_DataLoad::job::number_t> pres = activity.get_predecessors();
	auto pre_with_max_earlist_finish_time = scheduled_activities.find(pres[0]);
	auto iterator_to_cmp_with_PWMEFT = pre_with_max_earlist_finish_time;
	++iterator_to_cmp_with_PWMEFT ;
	for ( int count=1;
				count<pres.size() && iterator_to_cmp_with_PWMEFT!=scheduled_activities.end();
				++count){
		if(iterator_to_cmp_with_PWMEFT->second.get_ef() > 
			pre_with_max_earlist_finish_time->second.get_ef()){
				pre_with_max_earlist_finish_time = iterator_to_cmp_with_PWMEFT;
			}
	}
	// set earlies start time and earliest finish time for current activity
	// to satisfy resource-constrain
	time_concept::time_bucket::date_t earliest_start_time = pre_with_max_earlist_finish_time->second.get_ef();
	for(auto it=time_line_for_resource.begin() ; it != time_line_for_resource.end() ; ++it){
		if(activity.get_required_resources().at(it->first)!=0){
			if( !it->second.empty() ){
				time_concept::time_bucket::time_line::iterator tmp_date = it->second.begin();
				// find the time_bucket of the resource with the min val in which has bigger value of end than earliest start time 
				while(tmp_date != it->second.end() && earliest_start_time >= tmp_date->get_end() ){
					++tmp_date;
				}
				// if there is any confliction about resource change the earliest start time
				while(tmp_date != it->second.end() && 
							earliest_start_time + activity.get_duration() > tmp_date->get_begin()){
								if(tmp_date->get_holding_resource_size()+ activity.get_required_resources().at(it->first) > 
									limited_resources.at(it->first) && earliest_start_time < tmp_date->get_end()){
										earliest_start_time = tmp_date->get_end();
								}
								++tmp_date;
				}
			}
		}
	}
	activity.set_es(earliest_start_time).set_ef(earliest_start_time+activity.get_duration());

	// set time for resources
	for(auto it=time_line_for_resource.begin() ; it != time_line_for_resource.end() ; ++it){
		if(activity.get_required_resources().at(it->first)!=0){
			if( !it->second.empty() ){
				time_concept::time_bucket::time_line tmp_time_line;
				auto iterator_for_tmp_date_start = it->second.begin();
				while(iterator_for_tmp_date_start != it->second.end() && 
							earliest_start_time >= iterator_for_tmp_date_start->get_end()){
								++iterator_for_tmp_date_start;
				}
				auto iterator_for_tmp_date_new = iterator_for_tmp_date_start;
				auto keep_iter_loc = iterator_for_tmp_date_new;
				while(iterator_for_tmp_date_new != it->second.end()){
					if(earliest_start_time + activity.get_duration() > iterator_for_tmp_date_new->get_begin()){
						tmp_time_line.push_back(*iterator_for_tmp_date_new);
						++iterator_for_tmp_date_new;
					}else{
						break;
					}
				}
				time_concept::time_bucket::time_line time_line_for_split;
				time_concept::time_bucket::date_t walking_time = earliest_start_time;
				std::size_t cur_resource_size = activity.get_required_resources().at(it->first);
				for(auto i=iterator_for_tmp_date_start ; i!=iterator_for_tmp_date_new ; ++i){
					if(walking_time > i->get_end()){
						std::insert_iterator<time_concept::time_bucket::time_line> time_insert_iterator(it->second,i);
						if(earliest_start_time + activity.get_duration() < i->get_end()){
							auto behind_time = *i;
							auto middle_time = *i;
							behind_time.set_end(walking_time);
							middle_time.set_begin(walking_time)
							.set_end(earliest_start_time+activity
							.get_duration())
							.set_holding_resource_size(middle_time.get_holding_resource_size()+cur_resource_size);
							i->set_begin(earliest_start_time+activity.get_duration());
							time_insert_iterator = behind_time;
							time_insert_iterator = middle_time;
							walking_time = i->get_end();
						}else{
							auto behind_time = *i;
							behind_time.set_end(walking_time);
							i->set_begin(walking_time).set_holding_resource_size(i->get_holding_resource_size() + cur_resource_size);
							time_insert_iterator = behind_time;
							walking_time = i->get_end();
						}
					}else if (walking_time == i->get_begin()){
						std::insert_iterator<time_concept::time_bucket::time_line> time_insert_iterator(it->second,i);
						if(earliest_start_time+activity.get_duration() < i->get_end()){
							auto behind_time = *i;
							behind_time.set_end(earliest_start_time+activity.get_duration())
							.set_holding_resource_size(i->get_holding_resource_size() + cur_resource_size);
							i->set_begin(earliest_start_time+activity.get_duration());
							time_insert_iterator = behind_time;
							walking_time = i->get_end();
						}else{
							i->set_holding_resource_size(i->get_holding_resource_size() + cur_resource_size);
							walking_time = i->get_end();
						}
					}else{
						std::insert_iterator<time_concept::time_bucket::time_line> time_insert_iterator(it->second,i);
						if(earliest_start_time+ activity.get_duration() < i->get_end()){
							auto behind_time = *i;
							auto middle_time = *i;
							behind_time.set_begin(walking_time)
							.set_end(middle_time.get_begin())
							.set_holding_resource_size(cur_resource_size);
							middle_time.set_end(earliest_start_time+activity.get_duration())
							.set_holding_resource_size(middle_time.get_holding_resource_size()+cur_resource_size);
							i->set_begin(earliest_start_time+activity.get_duration());
							time_insert_iterator = behind_time;
							time_insert_iterator = middle_time;
							walking_time = i->get_end();
						}else{
							auto behind_time = *i;
							behind_time.set_begin(walking_time)
							.set_end(i->get_begin())
							.set_holding_resource_size(cur_resource_size);
							i->set_holding_resource_size(i->get_holding_resource_size()+cur_resource_size);
							time_insert_iterator = behind_time;
							walking_time = i->get_end();
						}
					}
				}
				if( walking_time < earliest_start_time + activity.get_duration()){
					std::insert_iterator<time_concept::time_bucket::time_line> time_insert_iterator(it->second,iterator_for_tmp_date_new);
					time_concept::time_bucket last_time(walking_time,earliest_start_time+activity.get_duration());
					last_time.set_holding_resource_size(cur_resource_size);
					time_insert_iterator = last_time;
				}
			}
		}
	}
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