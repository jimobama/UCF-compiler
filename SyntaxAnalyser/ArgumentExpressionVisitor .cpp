#include "stdafx.h"
#include "ArgumentExpressionVisitor.h"
#include "IExpression.h"
#include "IExpressionContext.h"
#include  "IParser.h"
#include "ExpressionType.h"
#include "ExpressionTypeVisitor.h"


using namespace obaro::parsers;


ArgumentExpressionVisitor::ArgumentExpressionVisitor(IParser *p) :
IExpressionVisitor(p)
{

}


IExpression * ArgumentExpressionVisitor::visit(IExpression *expr, IExpressionContext *cxt)
{
	Token *tok = this->__parser->scanner->xhsGetCurrentToken();
	if (tok->type == TokenClass::TYPES || tok->type == TokenClass::IDENTIFIER)
	{
		this->__parserArgument(expr,cxt);
	}//epsilon

	return NULL;
}

IExpression * ArgumentExpressionVisitor::__parserArgument(IExpression *expr, IExpressionContext *cxt)
{
	/*
	this->__parserTypeConst(expr,cxt);
	IDen
	ExpressionTypeVisitor *typeVisitor = new ExpressionTypeVisitor(this->__parser);
	type->accept(typeVisitor, cxt);

	//parser the variable

	*/

	return NULL;

}

IExpression *  ArgumentExpressionVisitor::__parserTypeConst(IExpression *expr, IExpressionContext *cxt)
{
	Token *tok = this->__parser->scanner->xhsGetCurrentToken();
	if (this->__parser->match("const"))
	{
		this->__parser->scanner->parserNextToken();

		ExpressionType *type = new ExpressionType();
		ExpressionTypeVisitor *typeVisitor = new ExpressionTypeVisitor(this->__parser);
		type->accept(typeVisitor, cxt);
	}
	else if (tok->type == TokenClass::TYPES)
	{
		__parserTypeConst(expr, cxt);
	}

	return NULL;
}