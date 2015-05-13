#ifndef ARGUMENT_IEXPR_H
#define ARGUMENT_IEXPR_H
#include "IExpressionVisitor.h"

namespace obaro
{
	namespace parsers
	{
		class ArgumentExpressionVisitor 
			:public IExpressionVisitor
		{

		private:
			IExpression *__parserArgument(IExpression *expr, IExpressionContext *cxt);
			IExpression *__parserTypeConst(IExpression *expr, IExpressionContext *cxt);
		public:
			ArgumentExpressionVisitor(IParser *);
			IExpression *visit(IExpression *, IExpressionContext *cxt = 0);
		};
	}
}

#endif

