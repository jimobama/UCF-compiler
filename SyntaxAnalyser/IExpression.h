#ifndef IEXPRESSION_H
#define IEXPRESSION_H


#ifdef SYNTAXANALYSER_EXPORTS
#define IEXPRESSION_API __declspec(dllexport)
#else
#define IEXPRESSION_API __declspec(dllimport)
#endif

#include <Node.h>
#include <string>
using namespace obaro::graphs;

namespace obaro
{
	namespace parsers
	{
		class IEXPRESSION_API IExpressionVisitor;
		class IEXPRESSION_API IExpressionContext;

		class IEXPRESSION_API  IExpression :public Node
		{
		protected:
			std::string name;
			 IExpression(std::string name);
		public:
			IExpression virtual *accept(IExpressionVisitor *visitor, IExpressionContext *cxt) = 0;

		};
	}
}

#endif