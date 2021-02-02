# if !defined(_TEMLATE_GA_H)
# define _TEMLATE_GA_H
namespace _HeuristicAlgorithm
{
namespace Template{
// check if it is in t
template <typename T,typename value_type,typename EqualFun=bool>
class RepeatIn{
  public:
  bool operator()(T& t,value_type& it,EqualFun equals){
    for(auto& item : t){
      if(equals(it,item)){
        return true;
      }
    }
    return false;
  }
  bool operator()(T& t,value_type& it){
    for(auto& item : t){
      if(T::value_type::equals(it,item)){
        return true;
      }
    }
    return false;
  }
};
} // Template
}// _HeuristicAlgorithm
# endif