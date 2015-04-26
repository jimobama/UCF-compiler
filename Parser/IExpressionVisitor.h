#ifndef IEXPRESSION_VISITOR_H_
#define IEXPRESSION_VISITOR_H_

namespace obaro
{
	namespace parsers
	{
		class IParser;
		class IExpressionContext;
		class IExpression;

		class IExpressionVisitor
		{
		public:
			IExpressionVisitor(IParser *parser);
			IExpression *visit(IExpression *expr, IExpressionContext * cxt);
		};

	}
}
	 

#endif 