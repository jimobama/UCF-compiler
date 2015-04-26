#ifndef IDENTIFIER_EXPRESSION_H
#define IDENTIFIER_EXPRESSION_H

#ifdef SYNTAXANALYSER_EXPORTS
#define  IDENTIFIER_IMPORT __declspec(dllexport)
#else 
#define  IDENTIFIER_IMPORT __declspec(dllimport)
#endif

#include"IExpression.h"

namespace obaro
{
	namespace parsers
	{
		class IdentifierExpression:public IExpression
		{
		public:
			IDENTIFIER_IMPORT IdentifierExpression(std::string name);
			IDENTIFIER_IMPORT IExpression virtual *accept(IExpressionVisitor *visitor, IExpressionContext *cxt);

		};
	}
}
#endif