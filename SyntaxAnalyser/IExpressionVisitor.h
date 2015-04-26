#ifndef IEXPRESSION_VISITOR_H
#define IEXPRESSION_VISITOR_H

#ifdef SYNTAXANALYSER_EXPORTS
#define IEXPRESSION_VISITOR_API __declspec(dllexport)
#else IEXPRESSION_VISITOR_API __declspec(dllimport)
#endif

/*
A base interface class for the IExpression Visitor classes in the program
The program will 
*/
namespace obaro
{
	namespace parsers
	{
		class IEXPRESSION_VISITOR_API IParser;
		class IEXPRESSION_VISITOR_API IExpression;
		class IEXPRESSION_VISITOR_API IExpressionContext;

		//The class expression Node visitor
		class  IEXPRESSION_VISITOR_API IExpressionVisitor
		{
		protected:
			IParser *__parser;
		public:
			IExpressionVisitor(IParser *parser);
			IExpression virtual * visit(IExpression *expr, IExpressionContext *cxt = 0) = 0;
		};
	}
}
#endif