#include "stdafx.h"
#include "IdentifierExpressionVisitor.h"
#include "IExpressionVisitor.h"
#include "IExpression.h"
#include "IExpressionContext.h"
#include "IParser.h"
#include "TokenClass.h"

using namespace obaro::parsers;
using namespace obaro::core;

IdentifierExpressionVisitor::IdentifierExpressionVisitor(IParser * parser) 
:IExpressionVisitor(parser)
{
	
}

/*
  The visit method , check if the syntax is right , then create a new node to store it
*/

IExpression * IdentifierExpressionVisitor::visit(IExpression* expr, IExpressionContext * cxt)
{
	if (__parser != NULL)
	{
		IExpression *expression = expr;
		Token *token=	__parser->scanner->xhsGetCurrentToken();
		if (token->type == TokenClass::IDENTIFIER)
		{
            //Identifier found now add to the tree 

			token = this->__parser->scanner->parserNextToken();
			this->__parser->scanner->xhsSetCurrentToken(token);
		}
		
		this->__parser->parserError("Expecting an identifier but " + token->sequence + " given at ", 1);
		return expression;
	}
	
	this->__parser->parserError("No parser specified to parser the identifier ",0);

}