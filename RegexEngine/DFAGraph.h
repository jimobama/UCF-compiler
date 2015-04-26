#ifndef DFA_GRAPH_H
#define DFA_GRAPH_H

// DFAGraph.cpp : Defines the entry point for the console application.
//
#ifdef REGEXENGINE_EXPORTS
#define DFA_GRAPH_API __declspec(dllexport)
#else
#define DFA_GRAPH_API __declspec(dllimport)
#endif

#include "stdafx.h"
#include <vector>
#include <set>
#include <iostream>
#include "IGraph.h"

namespace obaro
{
	namespace graphs
	{
		class State;
		class Transition;
		class DFAGraph :public IGraph
		{
		private:
			State *initial;
			static std::set<State*> *__staticVisitedNodes;
			static DFA_GRAPH_API  int32_t xmlFomatter;
			//methods
			bool isDeadEnd(State*);
			
			//static methjods
			static void  parserElement(IXmlReader *&r, uint32_t level = 0);
			static void skipNonElementType(IXmlReader *&r);
			static State*  parserNode(IXmlReader *&r);
			static void parserEdges(IXmlReader *&r, DFAGraph *&dfa, State*& node, int32_t nCounter);
			//static memebers
			static	DFAGraph* parserXmlGraphFile(IXmlReader*&reader);

			//wriiting the graph to file
			static void writeNode(IXmlWriter *&writer, State *node);
			static void formatWritter(IXmlWriter *&writer, int32_t counter = 1);
			static void createGraph(IXmlReader *&preader);
			

		protected:
			DFA_GRAPH_API virtual void reduce();	
			static DFA_GRAPH_API 	bool IsVisit(State *);
			static DFA_GRAPH_API  void  MarkVisit(State *);
		public:
			DFA_GRAPH_API DFAGraph();
			DFA_GRAPH_API DFAGraph(State *root);
			DFA_GRAPH_API  virtual ~DFAGraph();
			DFA_GRAPH_API 	State * delta(State* state, char ch);
			//Set the root state
			void setRootNode(State* state);
			void setAlphabet(std::set<char> apls);
			//Check if the state exists
			DFA_GRAPH_API 	bool hasNode(Node* state);
			DFA_GRAPH_API  void addNode(Node*);
			DFA_GRAPH_API  bool match(char* str);
			//DFA_GRAPH_API  void connect(Node*, Node*, const char c);
			
			static DFA_GRAPH_API  DFAGraph*  loadXMLGraph(std::wstring filename);
			static DFA_GRAPH_API void saveTo(DFAGraph *graph, std::wstring filename);
			//not import as DLL
			bool isStateIDExist(int32_t id);
			State* getStateByID(int32_t id);

		};

	}
}//end DFAGraph



#endif