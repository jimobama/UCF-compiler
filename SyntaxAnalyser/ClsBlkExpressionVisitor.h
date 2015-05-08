#ifndef CLS_BLK_EXPRESSION_VISITOR_H
#define CLS_BLK_EXPRESSION_VISITOR_H
#include "IExpressionVisitor.h"


namespace obaro
{
	namespace parsers
	{
		class IExpression;
		class IExpressionContext;
		class IParser;

		class ClsBlkExpressionVisitor:public IExpressionVisitor
		{
		private:
		IExpression *	__parserClsBody(IExpression *expr, IExpressionContext *cxt);
		IExpression * __parserType(IExpression *expr, IExpressionContext *cxt);
		public:
			ClsBlkExpressionVisitor(IParser *parser);
			IExpression *visit(IExpression *expr, IExpressionContext *cxt = 0);
		};
	}
}

#endif
