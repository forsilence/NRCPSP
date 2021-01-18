# if !defined(_HATEST_H)
# define _HATEST_H
# include "_HeuristicAlgorithm.h"
namespace _HeuristicAlgorithm
{
namespace Test
{
class TestBase: public HeuristicAlgorithmBase{
  public:
  virtual void run_test() =0 ;
  virtual std::string information();
  private:
  std::string test_information;
};
} // namespace Test

} // namespace _HeuristicAlgorithm

# endif