#ifndef QUALIFIER_EXPRESSION_VISITOR_H
#define QUALIFIER_EXPRESSION_VISITOR_H
#include "IExpressionVisitor.h"
namespace obaro
{
	namespace parsers
	{
		class ExpressionQualifierVisitor:public IExpressionVisitor
		{
		private:
			IExpression * __parserScopeModifier(IExpression *expr, IExpressionContext *cxt);
			IExpression * __parserScopeQualifier(IExpression *expr, IExpressionContext *cxt);
		public:
			ExpressionQualifierVisitor(IParser *_parser);
			IExpression * visit(IExpression *expr, IExpressionContext *cxt = 0);
		};
	}
}

#endif