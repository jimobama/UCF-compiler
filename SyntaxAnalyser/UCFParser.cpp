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
IExpression * UCFParser::parse()
{
	IExpression *expr = NULL;
	if (this->scanner->hasNextToken())
	{
		Token *token = scanner->parserNextToken();
		return  this->__parser(token);
		parse();
	}

}


IExpression *UCFParser::__parser(Token *tok)
{
	IExpression *__expr = NULL;
	
	if (tok!= NULL && tok->type != TokenClass::INVALID_TOKEN)
	{
		// switch tokens 
		switch (tok->type)
		{
			case TokenClass::QUALIFIER:
			case TokenClass::CLASS:
				return this->__parserClassDef();
			default:
			{
				this->parserError("Syntax error: unexpected token '" + tok->sequence + "' found at ", 1);
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
	ExpressionQualifierVisitor *qualifierVisit = new ExpressionQualifierVisitor(this);
	return exprQualifier->accept(qualifierVisit,NULL);
}