#ifndef EXPRESSION_QUALIFIER_H
#define EXPRESSION_QUALIFIER_H
#include "IExpression.h"

namespace obaro
{
	namespace parsers
	{
		class ExpressionQualifier:public IExpression
		{
			//Math
		public:
			ExpressionQualifier();
			IExpression *accept(IExpressionVisitor* visit, IExpressionContext *cxt);
		};
	}
}


#endif