// SyntaxAnalyser.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include"ParserIdentifier.h"
#include "IExpression.h"
#include "IdentifierExpression.h"
#include "IdentifierExpressionVisitor.h"



using namespace obaro::parsers;

ParserIdentifier::ParserIdentifier(LexicalAnalyser*& __scanner,int32_t pass) 
:IParser(__scanner,pass)
{

}

/* The parser is used to check if the current token is an identifier
if its an identifier it will then add it to the parser tree*/
IExpression * ParserIdentifier::parse()
{
	if (this->scanner == NULL)
	{
		this->parserError("There is no token stream to parser",0);
		return NULL;
	}
	else
	{

		Token *token = this->scanner->xhsGetCurrentToken();
		if (token == NULL || token->type != TokenClass::IDENTIFIER)
		{
			this->parserError("Expecting an identifier but invalid token find at ", 1);
			return NULL;
		}
		else{
			//else 

			IExpression* ident = (IExpression*) new IdentifierExpression(token->sequence);
			IdentifierExpressionVisitor *identVisitor = new  IdentifierExpressionVisitor(this);
			return ident->accept(identVisitor, this->context);
		}
	}

}




