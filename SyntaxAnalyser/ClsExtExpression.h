#ifndef CLS_EXT_EXPRESSION_H
#define CLS_EXT_EXPRESSION_H

#include "IExpression.h"

namespace obaro
{
	namespace parsers
	{
		class ClsExtExpression :public IExpression
		{
		public:
			ClsExtExpression();
			IExpression virtual *accept(IExpressionVisitor *visitor, IExpressionContext *cxt);
			

		};
	}
}
#endif