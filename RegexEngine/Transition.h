#ifndef TRANSITION_H
#define TRANSITION_H


#ifdef REGEXENGINE_EXPORTS
#define TRANSITION_GRAPH_API __declspec(dllexport)
#else
#define TRANSITION_GRAPH_API __declspec(dllimport)
#endif

#include "Edge.h"
/*Comment
*/
namespace obaro
{
	namespace graphs
	{
		class State;
		class TRANSITION_GRAPH_API  Transition :public Edge
		{
		private:
						
		public:			
			static const char EPSILON = (char)'\0';
			 State* getState();
		};
	}
}
#endif