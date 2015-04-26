
#ifndef GRAMMAR_LEXICONS_H
#define GRAMMAR_LEXICONS_H

#ifdef LEXICALANALYSER_EXPORTS
#define GRAMMAR_LEXICONS_API __declspec(dllexport)
#else
#define GRAMMAR_LEXICONS_API __declspec(dllimport)
#endif


#include <vector>
#include <NFAGraph.h>
#include <DFAGraph.h>
#include <TokenClass.h>
using namespace obaro::graphs;
using namespace obaro::core;

namespace obaro
{
	namespace lexical
	{
		class GrammarLexeme
		{

		private:
			std::vector<NFAGraph*>    __nfa;
			std::vector<std::string>    keywords;
			std::vector<std::string>    arithematic_operator;
			static	GrammarLexeme        *__instance;
			bool IsLoadFromDisk;
			void loadXMLLexicalNodes();
		public:
			//predefined
			static std::string	  LOWERCASE;
			static std::string	  UPPERCASE;
			static std::string	  DIGIT;
			static std::string    ALPHABET;
			static std::string    DOUBLE;
			static std::string    ALPH_NUMERIC;
			static std::string    WORD;
			static std::string	  INTEGER;
			static std::string    NUMBER;
			static std::string    SPECIAL_CHARACTERS;
			static std::string    STRING_LITERAL;
			static std::string    WHITE_SPACES;
			void clearGraph();
			void initalised();
			DFAGraph *combine();

			

			public:
				GRAMMAR_LEXICONS_API GrammarLexeme(bool s =false);
				GRAMMAR_LEXICONS_API void useDefault();
				GRAMMAR_LEXICONS_API void newLexicon(std::string regex, obaro::core::TokenClass id);				
		



		};

	}
}

#endif