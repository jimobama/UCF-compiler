#include "stdafx.h"
#include "IdentifierExpression.h"
#include "IExpressionVisitor.h"

using namespace obaro::parsers;

IdentifierExpression::IdentifierExpression(std::string name) 
	:IExpression(name)
{

}


IExpression * IdentifierExpression::accept(IExpressionVisitor *visitor, IExpressionContext * ctx)
{
	return visitor->visit(this, ctx);
}
