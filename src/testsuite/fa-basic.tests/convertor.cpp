#include "FA.h"
#include <iostream>

auto main() -> int
{
  // TODO: add more tests
  auto nfa_transitions = (fa::transition_table) { {{1,'a'},{1}} ,
						  {{1,'b'},{2}} ,
						  {{2,'a'},{2,1}} ,
						  {{2,'b'},{3}} ,
						  {{3,'a'},{3}} ,
						  {{3,'b'},{3}}};
  auto nfa = fa::finite_automata ({1,2,3},
				  {'a','b'},
				  {3},
				  1,
				  nfa_transitions);

  auto dfa = fa::convert_to_dfa (nfa);
  auto dfa_trans = dfa.get_transition_relations ();

  /*Print this new transition table on stdout.
   This is makeshift for now and would be moved in seperate function
   or would be replaced by automated testing of some kind. */
  for (const auto& tran : dfa_trans)
    {
      // state / symbol scanned
      std::cout <<tran.first.first<<" / "<<tran.first.second<<" -> ";

      // destination state
      std::cout <<"{ ";
      for (auto state : tran.second)
	{
	  std::cout<<state<<" ";
	}
      std::cout<<"}\n";
    }

  return 0;
}
