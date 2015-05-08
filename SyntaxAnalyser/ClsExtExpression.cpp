#include "stdafx.h"
#include "ClsExtExpression.h"
#include "IExpressionVisitor.h"
#include "IExpressionContext.h"
using namespace obaro::parsers;

ClsExtExpression::ClsExtExpression() 
	:IExpression("")
{

}
IExpression * ClsExtExpression::accept(IExpressionVisitor *visitor, IExpressionContext *cxt)
{

	return  visitor->visit(this, cxt);
}