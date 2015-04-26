
#ifndef STATE_H
#define STATE_H

#ifdef REGEXENGINE_EXPORTS
#define STATE_H_GRAPH_API __declspec(dllexport)
#else
#define STATE_H_GRAPH_API __declspec(dllimport)
#endif

#include "Node.h"
#include <set>
#include<stdint.h>
#include <TokenClass.h>

namespace obaro
{
	namespace graphs
	{


		class STATE_H_GRAPH_API State :public Node
		{
		private:
			void markFinalState();
		public:
			//public fields
			std::set<State*> states_nfa;
			TokenClass tokenID;		

			State(int32_t n);
			State(std::set<graphs::State*>& states, int32_t);
			//STATE_H_GRAPH_API  bool hasEdge(Edge *edge);
			void addEdge(graphs::Edge *edge);
		};

	}
}

#endif