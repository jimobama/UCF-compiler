#ifndef SC_EXPR_VIST_H
#define SC_EXPR_VIST_H
#include "IExpressionVisitor.h"

namespace obaro
{
	namespace parsers
	{
		class ScExpressionVisitor:public IExpressionVisitor
		{
		public:
			ScExpressionVisitor(IParser * parser);
			IExpression * visit(IExpression*, IExpressionContext *cxt = 0);
		};
	}
}


#endif

