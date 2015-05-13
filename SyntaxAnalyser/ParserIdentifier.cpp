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
	this->__expecting_str = "";
}

/* The parser is used to check if the current token is an identifier
if its an identifier it will then add it to the parser tree*/
IExpression * ParserIdentifier::parse(int32_t pass)
{
	   Token *token = this->scanner->xhsGetCurrentToken();
	   if (token != NULL){
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
			   if (this->__expecting_str.compare("") == 0)
			   {
				   this->excepting("an identifier");
			   }
			   this->parserError("Expecting " + this->__expecting_str + " but token  '" + token->sequence + "' find at ", 1);
			   return NULL;
		   }
		   }
		} 
	
}


void ParserIdentifier::excepting(std::string str)
{
	this->__expecting_str = str;
}



