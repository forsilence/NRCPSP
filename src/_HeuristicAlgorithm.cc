# include"../include/_HeuristicAlgorithm.h"
# include<iostream>
# include<sstream>
# include<algorithm>
namespace _HeuristicAlgorithm
{
namespace _DataLoad
{
// >>> job <<<
// @arg std::ostream
// @return std::ostream
std::ostream& job::print(std::ostream& out)
{
	out << "job_nb:" << job_nb << std::endl;
	out << "successors:" ;
	for(number_t it:successors){
		out << it << ' ' ;
	}
	out << std::endl;
	out << "predecussors:";
	for(number_t it:predecessors){
		out << it << " ";
	}
	out << std::endl;
	out << "duration:" << duration << std::endl;
	out << "required sources:" << std::endl;
	for( resource_elem_t it: required_resources){
		out << "resource " << it.first << " required size: " << it.second << std::endl;
	}
	return out;
}
std::string job::toString() const 
{
	std::string str;
	str += "job_nb-" + std::to_string(job_nb) + "\n";
	str += std::string("successors-") + "\n";
	for(auto it:successors){
		str += std::to_string(it)+" ";
	}
	str += "\n";
	str += "predecussors-\n";
	for(auto it:predecessors){
		str += std::to_string(it) + " ";
	}
	str += "\n";
	str += "duration-" + std::to_string(duration) + "\n";
	str += std::string("requiredSources-\n");
	for(auto it:required_resources){
		str += std::string("resource-")+std::to_string(it.first)+"-requiredSize-"
						+std::to_string(it.second) + "\n";
	}
	return str;
}
void infor_loader::load(std::string path)
{
	std::string file_type_dot_sm = ".sm";
	std::string file_type_dot_RCP = ".RCP";
	std::string::iterator dot_loc  = path.end();
	for(;dot_loc!=path.begin();dot_loc--){
		if(*dot_loc == file_type_dot_RCP[0]){
			break;
		}
	}
	if(std::equal(dot_loc,path.end(),file_type_dot_sm.begin())){
		text_h.load_text(path);
		load_dot_sm_file(path);
	}
	else if(std::equal(dot_loc,path.end(),file_type_dot_RCP.begin())){
		text_h.load_text(path);
		load_dot_RCP_file(path);
	}
	else {
		std::cout << "not write load for this kind of file" << std::endl;
		exit(1);
	}
}
// load .sm file
// @arg std::string
void infor_loader::load_dot_sm_file(std::string path)
{
	_M_th::text_handler::row_no_bulk_t rows_of_jobs = text_h.find_word_row_no("jobs");
	_M_th::text_handler::row_no_t first_row_no_of_jobs = rows_of_jobs[0];
	_M_th::text_handler::kv_t::iterator line_of_word_jobs_iterator = text_h.get_line_by_no(first_row_no_of_jobs);
	_M_th::line_handler lh(line_of_word_jobs_iterator->second);
	job::size_type jobs_size = std::atoi(lh.last()->c_str());//>>>jobs-size

	_M_th::text_handler::row_no_bulk_t rows_of_word_jobnr = text_h.find_word_row_no("jobnr.");
	_M_th::text_handler::kv_t::iterator iterator_start_by_word_jobnr = text_h.get_line_by_no(rows_of_word_jobnr[0]);
	job::number_t job_no=0;// job number
	job::size_type mode_size;
	job::size_type su_size;
	job::number_t su;//successors
	job::mode_t mode;//mode
	std::vector<job::mode_t> modes;//modes
	job::resource_bulk_t::key_type rkey;
	job::resource_t rec;
	std::vector<job::number_t> tmp_sus;
	job::duration_t duration;//duration
	job::resource_bulk_t res;

	std::map<job::number_t,std::vector<job::number_t>> store_predecessors;
	if(iterator_start_by_word_jobnr!=text_h.end_of_lines())
	for(++iterator_start_by_word_jobnr;
			job_no!=jobs_size;
			iterator_start_by_word_jobnr++)
	{
		// job_no
		// successors
		// predecessors(load)
		std::istringstream line(iterator_start_by_word_jobnr->second);
		line >> job_no >> mode_size >> su_size ;
		tmp_sus.clear();
		while(line >> su )
		{
			tmp_sus.push_back(su);
			// add predecessors
			std::map<   job::number_t,
									std::vector<job::number_t>>::iterator
					store_pred_iter = store_predecessors.find(su);
			if(store_pred_iter==store_predecessors.end()){
				std::vector<job::number_t> preds{job_no};
				store_predecessors.emplace(su,preds);
			}else{
				if( std::find(
								store_pred_iter->second.begin(),
								store_pred_iter->second.end(),
								job_no) == 
						store_pred_iter->second.end()
					)
					store_pred_iter->second.push_back(job_no);
			}
		}
		job new_job(job_no,tmp_sus);
		jobs.insert(no_job_elem_t(job_no,new_job));
	}
	else std::cout << "error!" << std::endl;

	iterator_start_by_word_jobnr = text_h.get_line_by_no(rows_of_word_jobnr[1]);
	job_no=0;
	if(iterator_start_by_word_jobnr!=text_h.end_of_lines())
	for(++(++iterator_start_by_word_jobnr);
			job_no!=jobs_size;
			iterator_start_by_word_jobnr++)
	{
		// mode
		// duration
		// required_resources
		// predecessors(add)
		std::istringstream line(iterator_start_by_word_jobnr->second);
		line >> job_no >> mode >> duration ;
		rec = 1;
		res.clear();
		while(line >> su_size){
			res.insert(job::resource_elem_t(rec++,su_size));
		}
		no_job_t::iterator job_iterator = find_job_by_no(job_no);
		job_iterator->second.set_duration(duration);
		job_iterator->second.set_required_resources(res);
		if(job_no!=1){// job 1 not add to store_predecessors
			job_iterator->second.set_predecessors(store_predecessors.at(job_no));
		}
	}else{
		std::cout << "error2!" << std::endl;
	}

	// init limited resources !
	rows_of_word_jobnr = text_h.find_word_row_no("RESOURCEAVAILABILITIES:");
	iterator_start_by_word_jobnr = text_h.get_line_by_no(rows_of_word_jobnr[0]);
	++(++iterator_start_by_word_jobnr);
	std::istringstream line(iterator_start_by_word_jobnr->second);
	rec = 1;
	while(line >> su_size){
		limited_resources.emplace(rec++,su_size);
	}
}

// load .RCP file
void infor_loader::load_dot_RCP_file(std::string path)
{
	// jobs-size limited-resources-size
	_M_th::text_handler::kv_t::iterator row_iterator = text_h.get_line_by_no(1);
	std::istringstream line(row_iterator->second);
	size_t jobs_size ;
	size_t limited_resources_size;
	line >> jobs_size >> limited_resources_size;
	// limited-resource-size
	size_t limited_resource_size;
	row_iterator = text_h.get_line_by_no(2);
	std::istringstream line_2(row_iterator->second);
	job::resource_t res_no = 1;
	for(int i=0;i<limited_resources_size;i++) {
		line_2 >> limited_resource_size;
		limited_resources.emplace(i+1,limited_resource_size);
	}
	// loading job information
	std::map<job::number_t,std::vector<job::number_t>> predecessors;
	for(int i=0;i<jobs_size;i++){
		row_iterator = text_h.get_line_by_no(3+i);
		std::istringstream row_line(row_iterator->second);
		job::duration_t duration;// duration
		row_line >> duration ;
		job::resource_bulk_t required_res;
		required_res.clear();
		for(int j=0;j<limited_resources_size; j++){//required-resources
			row_line >> limited_resource_size;
			required_res.emplace(j+1,limited_resource_size);
		}
		// successors
		// predecessors-store
		size_t successors_size ;
		row_line >> successors_size;
		std::vector<job::number_t> successors;
		job::number_t suc;
		while(row_line >> suc){
			successors.push_back(suc);
			predecessors[suc].push_back(i+1);
		}
		job new_job(i+1,successors);
		new_job.set_duration(duration);
		new_job.set_required_resources(required_res);
		jobs.emplace(i+1,new_job);
	}
	// set predecessors
	for(auto it:predecessors){
		jobs[it.first].set_predecessors(it.second);
	}
}

// @arg job::number_t
// @return infor_loader::no_job_t::iterator
infor_loader::no_job_t::iterator infor_loader::find_job_by_no(job::number_t no)
{
	return jobs.find(no);
}
// @return infor_loader::no_job_t::iterator
infor_loader::no_job_t::iterator infor_loader::end_of_jobs()
{
	return jobs.end();
}
// @arg job::resource_bulk_t
// @return void
void infor_loader::update_resources(job::resource_bulk_t rss)
{
	limited_resources.clear();//not need
	limited_resources = rss;
}
}// _DataLoad
// >>> default gene <<<
int& defaultGene::operator[](const size_t location) 
{
	return BaseGene[location];
}
size_t defaultGene::size() const
{
	return BaseGene.size();
}
void defaultGene::push_back(int a)
{
	BaseGene.push_back(a);
}
// >>> heuristicAlgorithmBase <<<

// @arg std::string $path log writed to 
void HeuristicAlgorithmBase::setLogWriterPath(std::string logPath)
{
	logWriter.set_file(logPath);
}
void HeuristicAlgorithmBase::logWriteIn(std::string logLine)
{
	logWriter.write_in(logLine);
}
void HeuristicAlgorithmBase::setLogBufferSize(size_t BSize)
{
	logWriter.set_buffer_size(BSize);
}
double HeuristicAlgorithmBase::Uniform(double min_,double max_)
{
	double distance = max_ - min_ ;
	double standar  =  rand()/32767.0;
	return distance*standar + min_ ;
}
}// _HeuristicAlgorithm