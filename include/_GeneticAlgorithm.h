# if ! defined(_GENETICALGORITHM_H)
# define _GENETICALGORITHM_H
# include"_BaseGeneticAlgorithm.h"
# include<vector>
# include<map>
# include<list>
namespace _HeuristicAlgorithm
{
class chromosome
{
	public:
	chromosome(std::size_t size_):MChromosome(size_){}
	int& operator[](size_t location);
	const int& operator[](size_t location) const ;
	void setVal(double val_);
	double getVal() const;
	std::size_t size() const;
	static bool cmp(const chromosome& first,const chromosome& second);
	static bool equals(const chromosome& a,const chromosome& b);
	private:
	std::vector<int> MChromosome;
	double val;
};
namespace time_concept{
class time_bucket{
	public:
	typedef std::list<time_bucket> time_line;
	typedef _DataLoad::job::date_t date_t;
	time_bucket(date_t begin_,date_t end_):begin(begin_),end(end_){}
	time_bucket& set_begin(date_t begin_) { 
		begin = begin_;
		return *this;
	}
	time_bucket& set_end(date_t end_) { 
		end = end_;
		return *this;
	}
	time_bucket& set_holding_resource_size(std::size_t size_){
		holding_resource_size = size_;
		return *this;
	}
	date_t get_begin() { return begin; }
	date_t get_end() { return end; }
	std::size_t get_holding_resource_size() const { return holding_resource_size; }
	private:
	date_t begin;
	date_t end;
	std::size_t holding_resource_size;
};
}// time_concept
class GeneticAlgorithm: public BaseGeneticAlgorithm
{
	public:
	typedef std::vector<chromosome> population_t;
	typedef std::multimap<_DataLoad::job::number_t,_DataLoad::job::number_t> cut_set_t;
	GeneticAlgorithm();
	GeneticAlgorithm(const int popSize_);
	GeneticAlgorithm(const int popSize_,const int maxGeneration_,const double mutateP_);
	virtual void run() override;

	virtual population_t initPop(size_t popSize,std::size_t chromosome_size);
	double schedule(const chromosome& ind);
	double objectiveFunction(chromosome& ind);
	virtual population_t selectParents(const population_t& pop);
	virtual population_t crossover(const population_t& selectedParents);
	virtual void mutate(chromosome& ind,double mutateP);
	virtual void popSort(population_t& pop);
	void update_cut_set(const no_job_t& sorted_activities, cut_set_t& cut_set,_DataLoad::job::number_t job_no);
	no_job_t::iterator max_priority( no_job_t& pr_queue,const chromosome& gene);
	void update_priority_activities(const no_job_t& sorted_activities,
																	const cut_set_t& cut_set,
																	no_job_t& free_activities,
																	no_job_t& priority_queue);
	bool eligible(const no_job_t& ,const _DataLoad::job& );
	std::vector<_DataLoad::job::number_t> topological_sort(const chromosome& ind);// tempral constrain
	no_job_t evaluate( const std::vector<_DataLoad::job::number_t>& topological_sort_res,
											const chromosome& gene);// resource constrain
	void set_time(_DataLoad::job& activity,
								std::map<_DataLoad::job::resource_t,
									time_concept::time_bucket::time_line>& time_line_for_resource,
								const no_job_t& scheduled_activities);
	void in_quik_sort(population_t& pop,int start,int end);
	std::size_t in_quik_sort_partition(population_t& pop,int start,int end); 
	protected:
	chromosome best_res;
};
namespace extract_function_from_GA{

} // extract_function_from_GA
}// _HeuristicAlgorithm
# endif