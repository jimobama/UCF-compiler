#ifndef IEXPRESSION_NODE_H_
#define IEXPRESSION_NODE_H_
#include <Node.h>
#include <string>
using namespace obaro::graphs;

namespace obaro
{
	namespace parsers
	{
		class IExpressionVisitor;
		class IExpressionContext;

		class IExpression :public Node
		{
		public:
			IExpression(const char*  lexeme);
			IExpression * accept(IExpressionVisitor *visitor, IExpressionContext * context = 0);
		};

	}
}
#endif