#include "FA.h"
#include <unordered_map>
#include <utility>
#include <set>

auto
get_next_unmarked_state (std::unordered_map <int, bool> &d_states)
{
  for (auto i = d_states.begin (); i != d_states.end (); ++i)
    {
      if (i->second == false)
	{
	  return i->first;
	}
    }
  return -1;
}

/*The function take's non detereminisitic finite autometa (NAF) and returns a
  deterministic finite autometa (DFA) that accepts the same language as NFA.  */ 
finite_autometa 
convert (const finite_autometa &nfa)
{
  // populate dstates with nfa states
  std::set <int> res_states;
  std::set <int> res_final_states = nfa.get_finalstates();
  
  auto nfa_states = nfa.get_states ();
  std::unordered_map <int, bool> d_states;
  std::unordered_map <std::pair <int, int>, int, pair_hash> d_tran;
  for (auto s: nfa_states)
    {
      d_states.insert ({s, false});
    }
  
  // initialy let's assume thre are no null transitions
  auto s = get_next_unmarked_state (d_states);
  while (s != -1)
    {
      //mark
      d_states [s] = true;
      
      for (auto symbol: nfa.get_input_chars ())
	{
	  auto new_state = nfa.move (s, symbol);
	  
	  if (d_states.find (new_state) != d_states.end ())
	    {
	      d_states.insert ({new_state, false});
	      if (res_final_states.find (new_state) != res_final_states.end ())
		res_final_states.insert (new_state);
	    }
	  
	  d_tran [{s,symbol}] = new_state;
	}
	    
      s = get_next_unmarked_state (d_states);
    }

  // make set of states 
  for (auto i: d_states)
    {
      res_states.insert (i.first);
    }
  
  auto dfa = finite_autometa (
}
