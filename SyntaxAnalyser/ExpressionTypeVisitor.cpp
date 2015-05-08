#include "stdafx.h"
#include "ExpressionTypeVisitor.h"
#include "IExpression.h"
#include "IExpressionContext.h"
#include "ParserIdentifier.h"
#include "IParser.h"

using namespace obaro::parsers;

ExpressionTypeVisitor::ExpressionTypeVisitor(IParser *parser) 
	:IExpressionVisitor(parser)
{

}


IExpression * ExpressionTypeVisitor::visit(IExpression *expr, IExpressionContext *cxt)
{
	IExpression *node = NULL;

	Token *tok = this->__parser->scanner->xhsGetCurrentToken();
	switch (tok->type)
	{
	case TokenClass::TYPES:
	{
		if (this->__parser->match("int") ||
			this->__parser->match("float") ||
			this->__parser->match("char") ||
			this->__parser->match("void"))
		{
			//do some here
			this->__parser->scanner->parserNextToken();
		}
	};
	case TokenClass::IDENTIFIER:
	{
		ParserIdentifier *parserIndent = new ParserIdentifier(this->__parser->scanner);
		node= parserIndent->parse();
		break;
	};
	default:
	{
		this->__parser->parserError("Syntax Error: Expecting a data type but this ' " + tok->sequence + "' token give", 1);
		break;
	}
	}

	return node;
}