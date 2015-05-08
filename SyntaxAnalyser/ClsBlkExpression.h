#ifndef CLS_BLK_EXPRESSION_H
#define CLS_BLK_EXPRESSION_H
#include "IExpression.h"

namespace obaro
{
	namespace parsers
	{
		class IExpressionContext;
		class ClsBlkExpression:public IExpression 
		{
		public:
			ClsBlkExpression();
			IExpression * accept(IExpressionVisitor *visitor, IExpressionContext *cxt);
		};
	}
}


#endif