#include <unordered_map>
#include <set>
#include <utility>

namespace fa
{

// Only for pairs of std::hash-able types for simplicity.
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

	//TODO: maybe use a better hashing method.
        return h1 ^ h2;  
    }
};


using state = int;
using symbol = char;
/*Each STATE on scanning a symbol maps to a set of states.  */
using transition_table =  std::unordered_map <std::pair <state, symbol>,
					      std::set <state>,
					      pair_hash>;


/* A finite autometa is a 5 tupple ( Q, sigma, delta, F, q0 ).  */
class finite_autometa
{
 public:
  
  finite_autometa (const std::set <state> states,
		   const std::set <symbol> input_alpha,
  		   const std::set <state> final_states,
		   const state initial_state,
		   transition_table relations);
    
  finite_autometa();
  
  auto move(state current_state, symbol scanned_symbol) const;
  //TODO: maybe a function to check sanity of the autometa.

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

} // namespace fa
