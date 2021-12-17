#include <unordered_map>
#include <set>
#include <utility>

// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

// a finite autometa is a 5 tupple ( Q, sigma, delta, F, q0 )
class finite_autometa
{
 public:
  
  finite_autometa (const std::set <int> states,
		   const std::set <char> input_apha,
  		   const std::set <int> final_states,
		   const int initial_state,
		   std::unordered_map <std::pair <int,int>, int> relations);
    
  finite_autometa();
  
  int move(int current_state, char symbol) const;
  // maybe a function to check sanity of the autometa;

  std::set <int> get_states () const {return m_Q;};
  std::set <char> get_input_chars () const {return m_input;};
  std::set <int> get_finalstates () const {return m_F;};
  int get_initialstate () const {return m_q0;};
  // const std::unordered_map <std::pair <int, int>, int> get_transition_relations ();
  
 private:
  bool m_is_DFA;
  const std::set <int> m_Q;
  const std::set <char> m_input;
  const std::set <int> m_F;
  const int m_q0;
  const std::unordered_map <std::pair <int, int>, int, pair_hash> m_tr;
};


