#ifndef CLS_EXT_EXPR_VISITOR_H
#define CLS_EXT_EXPR_VISITOR_H
#include "IExpressionVisitor.h"

namespace obaro
{
	namespace parsers
	{
		class IParser;
		class IExpression;
		class IExpressionContext;

		class ClsExtExpressionVisitor :public IExpressionVisitor
		{
		private:
			IExpression *__parserImplement(IExpression *expr, IExpressionContext *cxt);
			IExpression * __parserImplementExt(IExpression *expr, IExpressionContext *cxt);
			IExpression * __parserInheritExt(IExpression *expr, IExpressionContext *cxt);
		public:
			ClsExtExpressionVisitor(IParser *parser);
			IExpression *visit(IExpression *expr, IExpressionContext *cxt = 0);

		};
	}
}
#endif