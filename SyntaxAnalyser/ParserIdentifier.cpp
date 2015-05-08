// SyntaxAnalyser.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include"ParserIdentifier.h"
#include "IExpression.h"
#include "IdentifierExpression.h"
#include "IdentifierExpressionVisitor.h"
#include "IExpressionContext.h"



using namespace obaro::parsers;

ParserIdentifier::ParserIdentifier(LexicalAnalyser*& __scanner,int32_t pass) 
:IParser(__scanner,pass)
{

}

/* The parser is used to check if the current token is an identifier
if its an identifier it will then add it to the parser tree*/
IExpression * ParserIdentifier::parse()
{
	   Token *token = this->scanner->xhsGetCurrentToken();
		//parser it
		switch (token->type)
		{
		case TokenClass::IDENTIFIER:{
			IdentifierExpressionVisitor *indentVisitor = new IdentifierExpressionVisitor(this);
			IdentifierExpression *expr = new IdentifierExpression(token->sequence);			
			return expr->accept(indentVisitor, NULL);
		}
		default:
		{
			this->parserError("Expecting an identifier but token  '"+ token->sequence +"' find at ", 1);
			return NULL;
		}
		} 
	
}




