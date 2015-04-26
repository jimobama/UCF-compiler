
/*
  The class is the basic for all the parser IExpression Nodes
*/
#include "stdafx.h"
#include "IExpressionVisitor.h"
#include "IExpressionContext.h"
#include "IExpression.h"


using namespace obaro::parsers;

IExpression::IExpression(std::string name)
{
	this->name = name;
}