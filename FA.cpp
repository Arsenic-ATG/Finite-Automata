#include "FA.h"

/*Constructor of class finite_autometa.  */
finite_autometa::finite_autometa (const std::set <int> states,
				  const std::set <char> input_alpha,
				  const std::set <int> final_states,
				  const int initial_state,
				  std::unordered_map <std::pair <int,int>, int> relations )
  :m_Q (states), m_input (input_alpha), m_F (final_states), m_q0 (initial_state), m_tr (relations)
{
  //TODO: check if it's an DFA or not and set is_dfa accordingly
}

/*Function to move from one state to another based on the trasition relation
  defined by the autometa and return the value of new state reached by the
  autometa.
  return -1 in case the transition relation doesn't exist.  */
int
finite_autometa::move (int current_state, char symbol)
{
  auto new_state = m_tr.find({current_state,symbol});

  if (new_state != m_tr.end ())
    {
      return -1;
    }
  else
    return (new_state->second);
}
