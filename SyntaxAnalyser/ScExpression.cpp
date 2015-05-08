#include "stdafx.h"
#include "SCExpression.h"
#include "IExpressionVisitor.h"
#include "IExpressionContext.h"
#include <string>

using namespace obaro::parsers;

ScExpression::ScExpression(std::string name)
	:IExpression(name)
{

}

IExpression * ScExpression::accept(IExpressionVisitor * v, IExpressionContext * cxt)
{
	return v->visit(this, cxt);
}

