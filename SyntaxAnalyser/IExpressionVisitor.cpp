#include "stdafx.h"
#include "IExpressionVisitor.h"
#include "IExpressionContext.h"
#include "IExpression.h"
#include "IParser.h"


using namespace obaro::parsers;


IExpressionVisitor::IExpressionVisitor(IParser *parser)
{
	this->__parser = parser;
}