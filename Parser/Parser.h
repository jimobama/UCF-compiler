#ifndef PARSER_H
#define PARSER_H
#include<LexicalAnalyser.h>
#include<TokenClass.h>
#include"IParser.h"

using namespace obaro::lexical;

namespace obaro
{
	namespace parsers
	{

		class Parser:public IParser
		{
		private:
			LexicalAnalyser *analyser;
		};
	}
}

#endif