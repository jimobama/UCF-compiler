#ifndef EXPRESSION_TYPE_H
#define EXPRESSION_TYPE_H
#include "IExpression.h"


namespace obaro
{
	namespace parsers
	{
		class ExpressionType:public IExpression
		{
		public:
			ExpressionType();
			IExpression *accept(IExpressionVisitor *visit, IExpressionContext *cxt = 0);
		};
	}
}

#endif