#include "stdafx.h"
#include "IExpression.h"
#include "UCFParser.h"


using namespace obaro::parsers;


UCFParser::UCFParser(LexicalAnalyser *__lexer) :IParser(__lexer)
{

}

/*The method will parser the parents nodes  languages*/
IExpression * UCFParser::parse()
{
	return NULL;
}


IExpression *UCFParser::__parserPreprocessors()
{
	
	return NULL;
}

IExpression *UCFParser::__parserClassDef()
{
	
	return NULL;
}

IExpression *UCFParser::__parserGroupClass()
{
	
	return NULL;
}
