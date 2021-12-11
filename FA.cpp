#include "FA.h"

/* a finite autometa is a 5 tupple ( Q, sigma, delta, F, q0 )
class finite_autometa
{
 public:

  finite_autometa();
  
  int move(int current_state, char symbol);
  // maybe a function to check sanity of the autometa;
  
 private:
  bool is_NFA;
  std::set<int> Q;
  std::set<char> input;
  std::set<int> F;
  int q0;
  std::unordered_map<std::pair<int,int>, int>;
  
}
*/

/*Constructor of class finite_autometa.  */
finite_autometa::finite_autometa ();

/*Function to move from one state to another based on the trasition relation
  defined by the autometa and return the value of new state reached by the
  autometa.  */
int
finite_autometa::move (int current_state, char symbol)
{
  int new_state = tr [std::make_pair (current_state,symbol)];
  return new_state;
}
