# if! defined(_HEURISTICALGORITHM_H)
# define _HEURISTICALGORITHM_H
# include<map>
# include<vector>
# include<string>
# include"text_handler.h"
namespace _HeuristicAlgorithm
{
namespace _DataLoad
{
class job
{
	public:
		typedef unsigned int number_t;
		typedef size_t size_type;
		typedef unsigned int duration_t;
		typedef unsigned int mode_t;
		typedef unsigned int resource_t;
		typedef std::map<   resource_t ,
												size_type> resource_bulk_t;
		typedef std::pair<  resource_t ,
												size_type> resource_elem_t;
		typedef double date_t;

		job()=default;
		job(number_t J_nb,
				std::vector<number_t> Ss
				):  job_nb(J_nb),
						successors(Ss),
						required_resources(){}
		job(number_t J_nb,
				size_type Modes_size,
				size_type Ss_size,
				std::vector<number_t> Ss
				):  job(J_nb,Ss){}
		job(number_t J_nb,
				std::vector<mode_t> Successors,
				duration_t Duration,
				resource_bulk_t Required_resources
				):  job_nb(J_nb),
						successors(Successors),
						duration(Duration),
						required_resources(Required_resources){}

		number_t get_number() const { return job_nb; }
		void set_number(number_t j_n) { job_nb=j_n; }
		std::vector<mode_t> get_modes() const ;
		size_type get_successors_size() const { return successors.size(); }
		std::vector<number_t> get_successors() const { return successors; }
		void set_successors(std::vector<number_t> sus) { successors=sus; }
		duration_t get_duration() const { return duration; }
		void set_duration(duration_t dura) { duration = dura; }
		resource_bulk_t get_required_resources() const { return required_resources; }
		void set_required_resources(resource_bulk_t rrs) { required_resources = rrs; }
		void set_predecessors(std::vector<number_t> pdcs) { predecessors = pdcs; }
		std::vector<number_t> get_predecessors() const { return predecessors; }
		std::string date_format() const;

		job& set_es(date_t es) {
			earliest_start = es;
			return *this; 
		}
		job& set_ef(date_t ef) {
			earliest_finish = ef;
			return *this; 
		}
		job& set_ls(date_t ls) { 
			latest_start = ls;
			return *this;
		}
		job& set_lf(date_t lf) {
			latest_finish = lf;
			return *this;
		}
		job::number_t get_no() const { return job_nb; }
		date_t get_es() const { return earliest_start; }
		date_t get_ef() const { return earliest_finish; }
		date_t get_ls() const { return latest_start; }
		date_t get_lf() const { return latest_finish; }

		std::ostream& print(std::ostream& );
		std::string toString() const ;

	private:
		number_t job_nb;// 号码
		std::vector<number_t> successors;
		std::vector<number_t> predecessors;
		duration_t duration;
		resource_bulk_t required_resources;
		date_t earliest_start;// 最早开始时间
		date_t earliest_finish;// 最早结束时间
		date_t latest_start;// 最晚开始时间
		date_t latest_finish;// 最晚结束时间
};
// >>>information loader<<<
class infor_loader
{
	public:
		typedef std::map<job::number_t,job> no_job_t;
		typedef std::pair<job::number_t,job> no_job_elem_t;

		infor_loader() = default;
		infor_loader(std::string path): text_h(path),
																		jobs(),
																		limited_resources(){}
		void load(std::string path);

		void load_dot_sm_file(std::string );
		void load_dot_RCP_file(std::string );
		size_t size_of_jobs() const { return jobs.size(); }
		no_job_t::iterator find_job_by_no(job::number_t) ;
		no_job_t get_all_jobs_map() const { return jobs; }
		job::resource_bulk_t get_resources() const { return limited_resources; }
		void update_resources(job::resource_bulk_t rss);
		no_job_t::iterator begin_of_jobs() ;
		no_job_t::iterator end_of_jobs() ;
	private:
		_M_th::text_handler text_h;
		std::map<job::number_t,job> jobs;
		job::resource_bulk_t limited_resources;
};
}// _DataLoad
// >>> default gene <<<
class defaultGene
{
	public:
	defaultGene() = default;
	int& operator[](const size_t location);
	size_t size() const ;
	void push_back(int a);
	private:
	std::vector<int> BaseGene;
};
// >>> HeuristicAlgorithmBase <<<
class HeuristicAlgorithmBase: public _DataLoad::infor_loader
{
    public:
    HeuristicAlgorithmBase(std::string name_):name(name_),logWriter(){}
    virtual void run();
    void setLogWriterPath(std::string );
    void logWriteIn(std::string );
    void setLogBufferSize(size_t BSize);
		void into_file(){
			logWriter.in_to_file();
		}
    double Uniform(double min_,double max_);
		unsigned InitRandomSeed();
		std::string getName() const;
		void setName(std::string name);
    private:
    _M_th::text_writer logWriter;
		protected:
		std::string name;
};
}// _HeuristicAlgorithm
# endif