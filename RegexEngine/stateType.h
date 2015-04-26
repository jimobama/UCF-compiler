#ifndef NODE_STATE_H
#define NODE_STATE_H

#ifdef REGEXENGINE_EXPORTS
#define NODE_STATE_GRAPH_API __declspec(dllexport)
#else
#define NODE_STATE_GRAPH_API __declspec(dllimport)
#endif

namespace obaro
{
	namespace graphs
	{
		enum NODE_STATE_GRAPH_API StateType
		{
			NONE_STATE,
			INITIAL_STATE,
			FINAL_STATE	

		};
	}
}
#endif