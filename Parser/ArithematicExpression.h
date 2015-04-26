#ifndef ARITHEMATIC_EXPRESSION_H
#define ARITHEMATIC_EXPRESSION_H
#include "IExpression.h"
/* The class method 

*/
namespace obaro
{
	namespace parsers
	{
		class ArithemticExpression :public IExpression
		{
		public:
			ArithemticExpression(const char*  lexeme);
			IExpression * accept(IExpressionVisitor *visitor, IExpressionContext * context = 0);			

		};
	}
}
#endif