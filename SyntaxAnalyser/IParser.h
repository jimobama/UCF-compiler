
#ifndef I_PARSER_H
#define I_PARSER_H

#ifdef SYNTAXANALYSER_EXPORTS
#define IPARSER_IMPORT __declspec(dllexport)
#else
#define IPARSER_IMPORT __declspec(dllimport)
#endif

#include <LexicalAnalyser.h>
#include <TokenClass.h>
using namespace obaro::lexical;



namespace obaro
{
	namespace parsers
	{
		class IExpression;

		class IPARSER_IMPORT  IParser
		{
		protected:
			//create a lexical analysis			
			 int32_t  compiler_pass;
			 IParser(LexicalAnalyser *&lexer,int32_t pass=1);
		public:
			static int32_t ErrorCount;
			static bool Success;

			LexicalAnalyser  *scanner;
			virtual IExpression * parse()=0;
			virtual  bool match(std::string str);
			virtual  void parserError(std::string error, const int32_t type);
		};
	}

}


#endif