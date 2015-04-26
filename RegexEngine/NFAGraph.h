#ifndef NFA_GRAPH_H
#define NFA_GRAPH_H

#ifdef REGEXENGINE_EXPORTS
#define  NFA_GRAPH_API __declspec(dllexport)
#else
#define  NFA_GRAPH_API __declspec(dllimport)
#endif

#include<string>
#include <vector>
#include <stack>
#include <set>
#include <Language.h>
#include <TokenClass.h>
#include <SStream.h>
#include "IGraph.h"
#include<stdint.h>

namespace obaro
{

	namespace core
	{
		class NFA_GRAPH_API SStream;
		enum NFA_GRAPH_API TokenClass;
		class NFA_GRAPH_API Language;
	}
    namespace graphs
		{
			class State;
			class Transition;
			class DFAGraph;
			

			class NFAGraph :public IGraph
			{
			private:
				int32_t		next_state_counter;
				obaro::core::TokenClass	token_id;
				 Language	*lang;
				//The operator states 
				std::stack< std::pair<State*,State*> > OP_NFAState;

			public:
				NFA_GRAPH_API NFAGraph();
				NFA_GRAPH_API NFAGraph(Language *language, TokenClass token_id = TokenClass::IDENTIFIER);
				~NFAGraph();
				NFA_GRAPH_API	bool hasNode(Node*);
				NFA_GRAPH_API  void addNode(Node*) ;
				//NFA_GRAPH_API  void connect(Node*, Node*, const char c);			
				//Property<State*, NFAGraph> Initial;
			//members functions
				NFA_GRAPH_API void compile();				
				NFA_GRAPH_API DFAGraph *NFAGraph::toDFA();			
				static NFA_GRAPH_API void merge(State *node1, State *node2, State*& linkNode, const char c = EPSILON__);
			
			 protected:
			//	virtual void	 clearNFAStates();
				

			private:
				std::set<State*>						e_closure(std::set<State*> sets);
				std::set<State*>						e_closure(State *initial);
				std::set<State*>						move(std::set<State*> NFA_States, const char c);
				std::pair<State*,State*> pop();
				//	void											    question_get_all_inputs_state();
				void												concat();
				void												kleene_star();
				void												union_op();
				void												plus_op();
				void												push_new_state(const char c);
				void												final_state();
				//symbol_stream<symbol>                               get_all_inputs_state(std::set<state*> *NFA_States_);
				bool                                                is_input_unique(char c, std::set<char> &inputs);
				const bool						is_exits_in(std::set<State*>, State*);
				std::set<State*>*                       set_to_vector(std::vector<State*>* vectors);
				std::stack<State*>						set_to_stack(std::set<State*> sets);
				void									create_NFAutomata(obaro::core::SStream regex);

				

			};
		}
}


using namespace obaro::graphs;
using namespace obaro::core;


#endif