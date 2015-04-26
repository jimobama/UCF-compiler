#ifndef EDGE_H
#define EDGE_H


#ifdef REGEXENGINE_EXPORTS
#define  EDGE_GRAPH_API __declspec(dllexport)
#else
#define  EDGE_GRAPH_API __declspec(dllimport)
#endif

namespace obaro
{
	namespace graphs
	{
		class Node;
		class  Edge
		{
		private:
			char ch;
			Node *endPoint;
		public:
			Edge();			
			EDGE_GRAPH_API void setEndPoint(Node* node);
			EDGE_GRAPH_API Node * getEndPoint();
			EDGE_GRAPH_API void setLabel(char c);
			EDGE_GRAPH_API 	Node * getNode();
			EDGE_GRAPH_API char  getLabel();


		};
	}
}
#endif