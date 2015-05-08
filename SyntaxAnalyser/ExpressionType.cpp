#include "stdafx.h"
#include "ExpressionType.h"
#include "IExpressionContext.h"
#include "IExpressionVisitor.h"

using namespace obaro::parsers;


ExpressionType::ExpressionType() :IExpression("")
{

}

IExpression * ExpressionType::accept(IExpressionVisitor *v, IExpressionContext* cxt)
{
	return v->visit(this, cxt);
}