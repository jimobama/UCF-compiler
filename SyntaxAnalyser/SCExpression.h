#ifndef SC_EXPR_NODE_H
#define SC_EXPR_NODE_H
#include "IExpression.h"
namespace obaro
{
	namespace parsers
	{
		class ScExpression :public IExpression
		{
		public:
			ScExpression(std::string input);
			IExpression *accept(IExpressionVisitor *, IExpressionContext *cxt = 0);
		};
	}
}
#endif