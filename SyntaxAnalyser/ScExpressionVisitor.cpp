#include "stdafx.h"
#include "ScExpressionVisitor.h"
#include "IParser.h"
#include "IExpression.h"
#include "IExpressionContext.h"

using namespace obaro::parsers;

ScExpressionVisitor::ScExpressionVisitor(IParser * parser) :IExpressionVisitor(parser)
{

}

IExpression * ScExpressionVisitor::visit(IExpression * expr, IExpressionContext * cxt)
{
	Token *token = this->__parser->scanner->xhsGetCurrentToken();
	if (token != NULL)
	{
		if (this->__parser->match(";"))
		{
			this->__parser->scanner->parserNextToken();
		}
		else
		{
			this->__parser->parserError("Syntax Error: expecting a simi-colon but token '"+token->sequence+"' given at ", 0);
		}
	}

	return NULL;
}
