#ifndef IPARSER_H
#define IPARSER_H
#include <LexicalAnalyser.h>
using namespace obaro::graphs;
namespace obaro
{
	namespace parsers
	{
		class IParser
		{
		private:
			
		protected:			
			IParser(LexicalAnalyser *&lexer);
		public:
			IGraph *parser();

		};

	}
}
#endif