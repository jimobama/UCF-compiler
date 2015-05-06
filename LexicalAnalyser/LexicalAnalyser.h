#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#ifdef LEXICALANALYSER_EXPORTS
#define LEXICAL_ANALYSIS_API __declspec(dllimport)
#else
#define LEXICAL_ANALYSIS_API __declspec(dllimport)
#endif

/*The adaptor method will be use to listener to the tokens detection and string operations*/

#include <SStream.h>
#include <DFAGraph.h>
#include <TokenClass.h>
#include <State.h>
#include <stdint.h>

using namespace obaro::graphs;
using namespace obaro::core;



namespace obaro
{
	namespace io
	{
		class FileInputStream;
	}
	namespace lexical
	{
		class ILexicalListener;
		class GrammarLexeme;

		class LexicalAnalyser
		{
		protected:
		private:
			SStream *__symbolStream;
			io::FileInputStream *__filestream;
			ILexicalListener *__lexicalListener;
			std::string __pattern;
			int32_t  __lineNumber;
			int32_t __columnNumber;
			bool useSpecificationFromFile;

			//The Automata Machine Generator
			DFAGraph *dfaGraph;
			GrammarLexeme  *__lexemes;
			State* currentAcceptingState;
			//token
			Token *__currentToken;		
		 
		
			//listener events

		private:
			 bool __isPrepared;
			 void skipUntil(char c = ' ');
			//token helper member functions
			Token *__parserToken(State * start, char c);
			Token * __parserString(char c);
			Token * parserTokenStates(State *state, char c);
			void init(bool abool=false);
		protected:
			
		public:
			LEXICAL_ANALYSIS_API LexicalAnalyser(bool a = false);
			LEXICAL_ANALYSIS_API LexicalAnalyser(io::FileInputStream *stream,bool a=false);
			LEXICAL_ANALYSIS_API  virtual ~LexicalAnalyser();
			LEXICAL_ANALYSIS_API virtual void prepare();
			LEXICAL_ANALYSIS_API void setSource(io::FileInputStream *stream);
			//listeners
			LEXICAL_ANALYSIS_API void setListener(ILexicalListener * listener);
			LEXICAL_ANALYSIS_API void removeListener();
			//Return the next token each time the method is called 
			LEXICAL_ANALYSIS_API  Token *parserNextToken();
			LEXICAL_ANALYSIS_API bool hasNextToken();

			//helper supported methods
			
			void countLine(char c);
			bool isWhiteSpace(char);
			bool  isComment(char c);
			bool isDoubleQuotes(char c);
			void emitMessage(Token *, std::string s = "Invalid token found at");

			//friends methods
			void xhsResetSimulator();
			
			void xhsInsertChar(char c);
			void xhsAcceptingState(State* accepting);

			LEXICAL_ANALYSIS_API DFAGraph * xhsGetSimulator();
			LEXICAL_ANALYSIS_API void xhsSetCurrentToken(Token *);
			LEXICAL_ANALYSIS_API Token * xhsGetCurrentToken();
		};
	}
}


#endif