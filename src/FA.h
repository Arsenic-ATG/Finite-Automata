#ifndef FA_H
#define FA_H

#include <map>
#include <set>
#include <utility>

namespace fa
{

constexpr auto epsilon = 0;
using state = int;
using symbol = char;

/* Each STATE on scanning a symbol maps to a set of states.  */
using transition_table =  std::map <std::pair <state, symbol>,
				    std::set <state>>;

/* A finite autometa is a 5 tupple ( Q, sigma, delta, F, q0 ).  */
class finite_automata
{
 public:

  finite_automata (const std::set <state> states,
		   const std::set <symbol> input_alpha,
  		   const std::set <state> final_states,
		   const state initial_state,
		   transition_table relations);

  finite_automata (const state initial_state,
		   transition_table ralations,
		   const std::set <state> final_states);

  // TODO: make one for regex also.

  auto move (state current_state, symbol scanned_symbol) const -> std::set <state>;
  auto move (std::set <state> states, symbol scanned_symbol) const -> std::set <state>;

  auto epsilon_closure (state st) const -> std::set <state>;
  auto epsilon_closure (std::set <state> st) const -> std::set <state>;

  //TODO: maybe a function to check sanity of the automata.

  // Accessors
  auto get_states () const {return m_Q;};
  auto get_input_chars () const {return m_input;};
  auto get_finalstates () const {return m_F;};
  auto get_initialstate () const {return m_q0;};
  auto get_transition_relations () const
  { return m_tr; };

 private:

  bool m_is_DFA;
  const std::set <state> m_Q;
  const std::set <symbol> m_input;
  const std::set <state> m_F;
  const state m_q0;
  const transition_table m_tr;
};

auto calc_state_set (const transition_table &relations) -> std::set<state>;
auto convert_to_dfa (const finite_automata &nfa) -> finite_automata;
}    // namespace fa

#endif    // FA_H
