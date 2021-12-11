#include <unordered_map>
#include <set>
#include <utility>

// a finite autometa is a 5 tupple ( Q, sigma, delta, F, q0 )
class finite_autometa
{
 public:

  finite_autometa();
  
  int move(int current_state, char symbol);
  // maybe a function to check sanity of the autometa;
  
 private:
  const bool is_NFA;
  const std::set<int> Q;
  const std::set<char> input;
  const std::set<int> F;
  const int q0;
  const std::unordered_map<std::pair<int,int>, int> tr;
  
}

