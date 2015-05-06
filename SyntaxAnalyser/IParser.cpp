#include "stdafx.h"
#include "IParser.h"
#include "IExpression.h"
#include <iostream>

using namespace obaro::parsers;

//The constructor set the lexical analyser and the number of  times to compiler and gather variable before semantic
IParser::IParser(LexicalAnalyser *&lexical,int32_t pass)
{
	this->scanner = lexical;
	this->compiler_pass = pass;
}
bool  IParser::match(std::string str)
{
	if (str.compare(this->scanner->xhsGetCurrentToken()->sequence) != 0)
	{
		return false;
	}
	return true;
}

//Report error 
void IParser::parserError(std::string error, const int32_t type)
{	
	switch (type)
	{
	  case 0:
		 std::cerr << "\n" << error;
		 break;
	  default:
		  Token * token = this->scanner->xhsGetCurrentToken();
		  std::cerr << "\n" << error << " line " << token->lineNumber;
		  break;
	}
}

