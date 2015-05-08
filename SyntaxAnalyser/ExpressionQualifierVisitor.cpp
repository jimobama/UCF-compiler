#include "stdafx.h"
#include "ExpressionQualifierVisitor.h"
#include "IExpression.h"
#include "IParser.h"
#include "IExpressionContext.h"

using namespace obaro::parsers;

ExpressionQualifierVisitor::ExpressionQualifierVisitor(IParser *parser) :
IExpressionVisitor(parser)
{

}

IExpression * ExpressionQualifierVisitor::visit(IExpression *expr, IExpressionContext *cxt)
{
	//parser the nodes and create more nodes 
	IExpression *node = NULL;
	Token *tok=this->__parser->scanner->xhsGetCurrentToken();
	if (tok->sequence.compare("static") == 0
		|| tok->sequence.compare("const") == 0)
	{
		node = this->__parserScopeModifier(expr, cxt);
		node = this->__parserScopeQualifier(expr, cxt);
	}
	else
	{
		node = this->__parserScopeQualifier(expr, cxt);
		node = this->__parserScopeModifier(expr, cxt);
	}
	

	return node;	
}

IExpression * ExpressionQualifierVisitor::__parserScopeModifier(IExpression *expr, IExpressionContext *cxt)
{
	IExpression *node = NULL;
	if (this->__parser->match("static") || this->__parser->match("static"))
	{
		this->__parser->scanner->parserNextToken();
	}
	return node;
}
IExpression * ExpressionQualifierVisitor::__parserScopeQualifier(IExpression *expr, IExpressionContext *cxt)
{
	IExpression *node = NULL;

	if (this->__parser->match("public") ||
		this->__parser->match("private") ||
		this->__parser->match("protected") ||
		this->__parser->match("internal"))
	{
	  this->__parser->scanner->parserNextToken();
	}

	return node;
}