#include "FA.h"
#include <map>
#include <utility>
#include <set>
#include <stack>

/*Function to return epsilon closure of the set of nfa states T of the finite
  autometa FA.  */
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

/*Function to return epsilon closure of a state T of the finite autometa FA.  */
auto
epsilon_closure (fa::state t,
		 const fa::finite_autometa &fa)
{
  auto fa_trans = fa.get_transition_relations ();
  auto fa_states = fa.get_states ();

  std::stack <fa::state> st;
  st.push (t);

  auto e_t = std::set ({t});
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

/*The function take's non detereminisitic finite autometa (NAF) and returns a
  deterministic finite autometa (DFA) that accepts the same language as NFA.  */
auto
convert (const fa::finite_autometa &nfa)
{
  auto s0 =  epsilon_closure (std::set ( {nfa.get_initialstate ()}),
			       nfa);

  /* the idea is that every dfa state is a set of nfa states.  */
  auto dfa_states = std::set ({s0});

  auto input_symbols = nfa.get_input_chars ();
  fa::transition_table dfa_trans;

  auto unmarked_states = dfa_states;
  /* unmark all the nfa states.  */
  for (auto nfa_state: nfa.get_states ())
    {
      unmarked_states.insert (std::set ({nfa_state}));
    }

  while (! unmarked_states.empty ())
    {
      auto T = unmarked_states.extract (unmarked_states.begin ());
      for (auto symbol: input_symbols)
	{
	  auto u = epsilon_closure (nfa.move (T.value (),symbol), nfa);
	  if (!dfa_states.count (u))
	    {
	      dfa_states.insert (u);
	      unmarked_states.insert (u);
	    }
	}
    }

  // final dfa
}
