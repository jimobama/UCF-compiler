// TestLexicalAnalayser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <LexicalAnalyser.h>
#include <FileInputStream.h>
#include <TokenClass.h>

using namespace obaro::lexical;
using namespace obaro::io;

int _tmain(int argc, _TCHAR* argv[])
{

	LexicalAnalyser *__lexer = new LexicalAnalyser(new FileInputStream("Hello.ucf"));
	__lexer->prepare();
	Token* token = __lexer->parserNextToken();
	while (token != NULL && token->type != TokenClass::INVALID_TOKEN)
	{
		std::cout << "\nToken Found : " << token->sequence;
		token = __lexer->parserNextToken();
	}

	getchar();
	return 0;
}

