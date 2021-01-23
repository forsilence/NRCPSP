# if ! defined( _GENETICALGORITHMTEST_H)
# define _GENETICALGORITHMTEST_H
# include"_HATest.h"
namespace _HeuristicAlgorithm
{
namespace Test
{
class GAScheduleTest: public TestBase{
  public:
  void run_test() override ;
};
class GAInitPopTest: public TestBase{
  public:
  void run_test() override ;
};
class GASelectParents: public TestBase{
  public:
  void run_test() override ;
};
class GACrossoverTest: public TestBase{
  public:
  void run_test() override ;
};
} // namespace Test

} // namespace _HeuristicAlgorithm
# endif