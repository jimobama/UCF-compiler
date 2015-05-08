#ifndef CLASS_EXPRESSION_PARSER_H
#define CLASS_EXPRESSION_PARSER_H
#include "IParser.h"
#include <LexicalAnalyser.h>
using namespace obaro::lexical;
namespace obaro
{
	namespace parsers
	{
		class  ParserDefClass:public IParser
		{
		private:
			//helper methods
			IExpression *  __parserClsExt();
			IExpression * __parserClsBlk();
		public:
			ParserDefClass(LexicalAnalyser *_lexer, int32_t level = 1);
			virtual IExpression * parse(int32_t pass = 0);
		};
	}
}

#endif