#include "stdafx.h"
#include "IExpression.h"
#include "UCFParser.h"
#include "ParserIdentifier.h"
#include "ParserDefClass.h"
#include "ExpressionQualifier.h"
#include "ExpressionQualifierVisitor.h"
#include <TokenClass.h>


using namespace obaro::parsers;
using namespace obaro::core;

UCFParser::UCFParser(LexicalAnalyser *__lexer) :IParser(__lexer)
{
	
}

/*The method will parser the parents nodes  languages*/
IExpression * UCFParser::parse(int32_t pass)
{
	IExpression *expr = NULL;
	Token *tok = NULL;
	if (this->scanner->hasNextToken())
	{
		
		if (pass == 0){
			tok = scanner->parserNextToken();
			pass++;
		}
		else{
			tok = scanner->xhsGetCurrentToken();
		}

		if (tok != NULL && tok->type != TokenClass::INVALID_TOKEN)
		{			
			expr = this->__parser(tok);
			expr = parse(pass);
		}
		//recursive the called
		
	}
	return expr;

}


IExpression *UCFParser::__parser(Token *tok)
{
	IExpression *__expr = NULL;	
	if (tok != NULL){
		// switch tokens 
		switch (tok->type)
		{
		case TokenClass::QUALIFIER:
		case TokenClass::CLASS:
			return this->__parserClassDef();
		default:
		{
			this->parserError("Syntax error: unexpected token '" + tok->sequence + "' found at ", 1);
			this->scanner->parserNextToken();
			break;
		}
		}//switch
	}
	return __expr;
}

IExpression * UCFParser::__parserClassDef()
{
	this->__parserQualifiers();
	ParserDefClass *clsParser = new ParserDefClass(this->scanner, 1);
	return clsParser->parse();
}
IExpression * UCFParser::__parserQualifiers()
{
	ExpressionQualifier *exprQualifier = new ExpressionQualifier();
	ExpressionQualifierVisitor *qualifierVisit;
	qualifierVisit  = new ExpressionQualifierVisitor(this);
	return exprQualifier->accept(qualifierVisit,NULL);
}