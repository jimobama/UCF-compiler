#ifndef IDENTIFIER_EXPRESSION_VISITOR_H
#define IDENTIFIER_EXPRESSION_VISITOR_H


#include "IExpressionVisitor.h"
namespace obaro
{
	namespace parsers
	{
		class IParser;
		class IdentifierExpressionVisitor:public IExpressionVisitor
		{			
		public:
			IEXPRESSION_VISITOR_API IdentifierExpressionVisitor(IParser *parser);
			IEXPRESSION_VISITOR_API IExpression virtual * visit(IExpression *expr, IExpressionContext *cxt = 0);
		};
	}
}

#endif