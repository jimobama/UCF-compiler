#ifndef IGRAPH_H
#define IGRAPH_H
#ifdef REGEXENGINE_EXPORTS
#define I_GRAPH_API __declspec(dllexport)
#else
#define  I_GRAPH_API __declspec(dllimport)
#endif
#include<set>
#include<vector>
#include<stdint.h>
#include<string>
#include <shlwapi.h> 
#include <ole2.h> 
#include <xmllite.h> 
#include <atlbase.h>
#pragma warning(disable : 4127)  // conditional expression is constant 

#define EPSILON__ (char)'\0'
namespace obaro
{
	namespace graphs
	{
		class Node;
		class Edge;
		
		class IGraph
		{
		private:
				
		
		protected:
			Node *initial;
			std::set<char> alphabets;
			std::vector < Node* > states;			
			 std::set<Node*> visitedNodes;	
			
			//writers
			
			

		
		protected:
			int32_t counter;			
			I_GRAPH_API virtual	void printNode(Node * n = NULL);
			I_GRAPH_API virtual	bool isVisit(Node *);
		    I_GRAPH_API  virtual void markVisit(Node *);
		
			I_GRAPH_API IGraph();
		public:
			I_GRAPH_API virtual	void print();
		
			I_GRAPH_API  virtual bool hasNode(Node*) { return false; };
			I_GRAPH_API  virtual	void addNode(Node*){};
			I_GRAPH_API  virtual void connect(Node*, Node*, const char c = EPSILON__);
			I_GRAPH_API  virtual std::vector <Node*>* getNodes();
			I_GRAPH_API  virtual int32_t size();
			I_GRAPH_API  virtual void	setInitial(Node* initial);
			I_GRAPH_API  virtual Node*	getInitial();
			I_GRAPH_API  virtual std::set<char> getCharacterSets();
			I_GRAPH_API  virtual void addCharacter(char c);
			I_GRAPH_API  virtual void addAllCharacters();
			

			
			
		

		};
	}
}


#endif