#ifndef NODE_H
#define NODE_H

#ifdef REGEXENGINE_EXPORTS
#define NODE_GRAPH_API __declspec(dllexport)
#else
#define  NODE_GRAPH_API __declspec(dllimport)
#endif

#include<vector>
#include<stdint.h>
#include "stateType.h"

namespace obaro
{
	namespace graphs
	{
		class Edge;
		class Node
		{

		protected:
			std::vector<Edge*> edges;
			int32_t n;
	
		public:
			StateType state;
			NODE_GRAPH_API Node(int32_t n = 0);
			NODE_GRAPH_API void  setN(int32_t n){ this->n= n; }
			NODE_GRAPH_API int32_t  getN(){ return n; }
			NODE_GRAPH_API virtual bool hasEdge(Edge *edge);
			NODE_GRAPH_API virtual void addEdge(Edge *edge);
			NODE_GRAPH_API virtual void removeEdge(Edge*);
			NODE_GRAPH_API std::vector<Edge*> Edges();

		};
	}//end edge
}

#endif