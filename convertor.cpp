#include "FA.h"
#include <unordered_map>
#include <utility>
#include <set>
#include <stack>

/*Function to return epsilon closure of the state of the finite autometa.  */
auto
epsilon_closure (std::set <fa::state> t,
		 const fa::finite_autometa &fa)
{
  auto fa_trans = fa.get_transition_relations ();
  auto fa_states = fa.get_states ();

  std::stack <fa::state> st;

  // push all states of T on stack ST
  for (auto a: t)
    {
      st.push (a);
    }

  auto e_t = t;
  while (!st.empty ())
    {
      auto top = st.top ();
      st.pop ();

      for (auto current_state: fa_states)
	{
	  auto reachable_states = fa.move (current_state, fa::epsilon);
	  if (reachable_states.count (top)
	      && (!e_t.count (current_state)))
	    {
	      e_t.insert (current_state);
	      st.push (current_state);
	    }
	}
    }

  return e_t;
}

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
auto
convert (const fa::finite_autometa &nfa)
{
  // populate dstates with nfa states
  std::set <int> res_states;
  std::set <int> res_final_states = nfa.get_finalstates();

  auto nfa_states = nfa.get_states ();
  std::unordered_map <int, bool> d_states;
  fa::transition_table d_tran;
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

  // final dfa
  // auto dfa = finite_autometa (
}
