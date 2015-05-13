#ifndef ARGUMENT_EXPR_H
#define ARGUMENT_EXPR_H 
#include "IExpression.h"

namespace obaro
{
	namespace parsers
	{
		class ArgumentExpression:public IExpression
		{
		public:
			ArgumentExpression();
			IExpression *accept(IExpressionVisitor *, IExpressionContext*cxt = 0);

		};
	}
}

#endif