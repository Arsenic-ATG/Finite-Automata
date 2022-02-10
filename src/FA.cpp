#include "FA.h"
#include <stack>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
using namespace fa;

/**
Constructor of class finite_autometa.
*/
finite_automata::finite_automata (const std::set <state> states,
				  const std::set <symbol> input_alpha,
				  const std::set <state> final_states,
				  const state initial_state,
				  transition_table relations)
  :m_Q (states), m_input (input_alpha), m_F (final_states), m_q0 (initial_state), m_tr (relations)
{
  //TODO: check if it's an DFA or not and set is_dfa accordingly
}

/**
Constructor of class finite_autometa.
*/
finite_automata::finite_automata (const std::set <symbol> input_alpha,
                                  const state initial_state,
				  transition_table relations,
				  const std::set <state> final_states)
  :m_Q (calc_state_set (relations)), m_input (input_alpha), m_F (final_states), m_q0 (initial_state), m_tr (relations)
{
}

/**
Constructor of class finite_autometa.
*/
finite_automata::finite_automata (const state initial_state,
				  transition_table relations,
				  const std::set <state> final_states)
  :m_Q (calc_state_set (relations)), m_input (calc_input_alpha (relations)), m_F (final_states), m_q0 (initial_state), m_tr (relations)
{
}

/**
Function to move from one state to another based on the trasition
relation defined by the autometa and return the set of new states
the autometa can move to and return empty set in case the transition
relation doesn't exist.
*/
std::set <state>
finite_automata::move (state current_state, symbol input_symbol) const
{
  auto new_state = m_tr.find({current_state, input_symbol});

  if (new_state != m_tr.end ())
    {
      return (new_state->second);
    }

  return {};
}


/**
Function to move from a set of states to another based on the trasition
relation defined by the autometa and return the set of new states the autometa
can move to and return empty set in case the transition relation doesn't
exist.
*/
std::set <state>
finite_automata::move (std::set<state> states, symbol input_symbol) const
{
  std::set <state> destination_set;
  for (auto current_state: states)
    {
      auto new_states = move (current_state, input_symbol);

      for (auto dest_state: new_states)
	{
	  destination_set.insert (dest_state);
	}
    }
  return destination_set;
}

/*simulate finite automata to recognize string WORD.  */
bool
finite_automata::simulate (std::string word) const
{
  auto possible_dest = epsilon_closure (m_q0);

  for (auto &current_char_itr : word)
    {
      possible_dest = epsilon_closure (move (possible_dest,
                                             current_char_itr));
    }

  std::set<int> intersection;
  std::set_intersection(m_F.begin (), m_F.end (),
                        possible_dest.begin (),possible_dest.end (),
                        std::inserter(intersection,
                                      intersection.end()));

  if (intersection.empty ()) return false;
  return true;
}


/**
epsilon_closure of state ST ( fo the current FA) is a set of states
that are reachable from the state St wihout scanning a symbol from
the tape (on an epsilon move).
*/
std::set <state>
finite_automata::epsilon_closure (state st) const
{
  auto stack = (std::stack <state>) {};
  stack.push (st);

  auto e_closure = std::set ({st});
  while (!stack.empty ())
    {
      auto top = stack.top ();
      stack.pop ();

      for (auto current_state: m_Q)
	{
	  if (move (current_state, epsilon).count (top)
	      && !(e_closure.count (current_state)))
	    {
	      e_closure.insert (current_state);
	      stack.push (current_state);
	    }
	}
    }

  return e_closure;
}

/**
calculate epsilon_clsore of a compaund state ST (represented as a set of states ).
*/
std::set <state>
finite_automata::epsilon_closure (std::set <state> st) const
{
  auto stack = (std::stack <state>) {};

  for (auto current_state: st) stack.push (current_state);

  auto e_closure = st;
  while (!stack.empty ())
    {
      auto top = stack.top ();
      stack.pop ();

      for (auto current_state: m_Q)
	{
	  if (move (current_state, epsilon).count (top)
	      && !(e_closure.count (current_state)))
	    {
	      e_closure.insert (current_state);
	      stack.push (current_state);
	    }
	}
    }

  return e_closure;
}

/**
Utility function to calculate state set from given transition
relations.
*/
std::set<state>
fa::calc_state_set (const transition_table &relations)
{
  auto states = std::set <fa::state> {};

  for (auto transition: relations)
    {
      states.insert (transition.first.first);
      for (auto st: transition.second)
	{
	  states.insert (st);
	}
    }
  return states;
}

/**
Utility function to calculate set of input alphabets from given
transition relations.
*/
std::set<symbol>
fa::calc_input_alpha (const transition_table &relations)
{
  auto input_alpha= std::set <fa::symbol> {};

  for (auto transition: relations)
    {
      input_alpha.insert (transition.first.second);
    }

  return input_alpha;
}

/**
Function to convert given NFA to equivalant DFA via subset
construction method. The function doesn't gurentee the DFA to be
minimised DFA.
*/
finite_automata
fa::convert_to_dfa (const finite_automata &nfa)
{

  auto nfa_final_state = nfa.get_finalstates ();
  auto s0 = nfa.epsilon_closure (nfa.get_initialstate ());

  // The idea is that every dfa state is a set of nfa states.
  using dfa_state = std::set <state>;
  auto dfa_states = std::set ({s0});

  auto input_symbols = nfa.get_input_chars ();

  std::map <std::pair <dfa_state, fa::symbol>,
	    dfa_state> dfa_trans;

  auto unmarked_states = dfa_states;

  while (! unmarked_states.empty ())
    {
      auto temp_state = unmarked_states.extract (unmarked_states.begin ());

      for (auto current_symbol: input_symbols)
	{
	  auto u = nfa.epsilon_closure (nfa.move (temp_state.value (),
						  current_symbol));
	  if (!dfa_states.count (u))
	    {
	      dfa_states.insert (u);
	      unmarked_states.insert (u);
	    }

	  dfa_trans [{temp_state.value (), current_symbol}] = u;
	}
    }

  /*Filter-pass: create a standard finite automata out of this
    transition table table.  */
  auto dfa_code_map = std::map <dfa_state, state> {};
  auto final_dfa_states = std::set <state> {};
  auto final_dfa_trans = (transition_table) {};
  auto final_dfa_final_states = final_dfa_states;

  auto state_counter = 1u;

  for (auto current_state: dfa_states)
    {
      final_dfa_states.insert (state_counter);
      dfa_code_map [current_state] = state_counter++;
    }

  for (auto transition : dfa_trans)
    {
      auto source = std::make_pair (dfa_code_map [transition.first.first],
                                   transition.first.second);
      auto destination = std::set <state> {dfa_code_map [transition.second]};

      final_dfa_trans [source] = destination;
    }

  auto final_dfa_init_state = dfa_code_map [s0];

  return finite_automata (final_dfa_states,
			  nfa.get_input_chars (),
			  final_dfa_final_states,
			  final_dfa_init_state,
			  final_dfa_trans);
}
