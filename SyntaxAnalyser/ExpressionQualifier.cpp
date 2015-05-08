#include "stdafx.h"
#include "ExpressionQualifier.h"
#include "IExpressionContext.h"
#include "IExpressionVisitor.h"

using namespace obaro::parsers;

ExpressionQualifier::ExpressionQualifier():
IExpression("")
{

}

IExpression * ExpressionQualifier::accept(IExpressionVisitor *v, IExpressionContext *cxt)
{
	//carryout content add to symbol tables and informations tracking
	return v->visit(this, cxt);
}