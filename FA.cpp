#include "FA.h"
using namespace fa;

/*Constructor of class finite_autometa.  */
finite_autometa::finite_autometa (const std::set <state> states,
				  const std::set <symbol> input_alpha,
				  const std::set <state> final_states,
				  const state initial_state,
				  transition_table relations)
  :m_Q (states), m_input (input_alpha), m_F (final_states), m_q0 (initial_state), m_tr (relations)
{
  //TODO: check if it's an DFA or not and set is_dfa accordingly
}

/*Function to move from one state to another based on the trasition relation
  defined by the autometa and return the set of new states the autometa can move
  to and return empty set in case the transition relation doesn't exist.  */
auto
finite_autometa::move (state current_state, symbol input_symbol) const
{
  auto new_state = m_tr.find({current_state, input_symbol});
  
  if (new_state != m_tr.end ())
    {
      return new_state;
    }
  
  new_state = {};
  return new_state;
}
