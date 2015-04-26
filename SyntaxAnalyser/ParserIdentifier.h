#ifndef IDENTIFIER_PARSER_H
#define IDENTIFIER_PARSER_H

#ifdef SYNTAXANALYSER_EXPORTS
#define  IDENT_IMPORT __declspec(dllexport)
#else 
#define  IDENT_IMPORT __declspec(dllimport)
#endif
#include "IParser.h"
#include "LexicalAnalyser.h"
using namespace obaro::lexical;

namespace obaro
{
	namespace parsers
	{
		class IExpressionContext;

		class ParserIdentifier :public IParser
		{
		public:
			IExpressionContext *context;
			IDENT_IMPORT ParserIdentifier(LexicalAnalyser *&_scanner, int32_t pass = 1);
			IDENT_IMPORT virtual IExpression * parse();
			
		};
	}

}

#endif

