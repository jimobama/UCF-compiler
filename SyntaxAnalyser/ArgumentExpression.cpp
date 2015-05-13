#include "stdafx.h"
#include "ArgumentExpression.h"
#include "IExpressionVisitor.h"
#include "IExpressionContext.h"

using namespace obaro::parsers;

ArgumentExpression::ArgumentExpression() 
	:IExpression("")
{

}

IExpression * ArgumentExpression::accept(IExpressionVisitor * visitor, IExpressionContext * cxt)
{
	return visitor->visit(this, cxt);
}