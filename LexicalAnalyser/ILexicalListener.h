#ifndef LEXICAL_LISTENER_H
#define LEXICAL_LISTENER_H

#ifdef LEXICALANALYSER_EXPORTS
#define LEXICAL_LISTENER_API __declspec(dllexport)
#else
#define LEXICAL_LISTENER_API __declspec(dllimport)
#endif

#include <TokenClass.h>
#include <SStream.h>
#include <State.h>
#include <DFAGraph.h>
#include <TokenClass.h>

using namespace obaro::graphs;
using namespace obaro::core;

namespace obaro
{
	namespace lexical
	{
		class LexicalAnalyser;
	
		class ILexicalListener
		{

		private:
			LexicalAnalyser *__analyser;
			bool isNormalInput(char, char);
		protected:
				
			

			//event handler
		public:
			LEXICAL_LISTENER_API ILexicalListener(LexicalAnalyser *listener = NULL);
			LEXICAL_LISTENER_API void attach(LexicalAnalyser *lsitener);
			//State Detector listeners
			Token * detectAcceptState(DFAGraph*, SStream *&stream,State* state);			
			//Token detectors
			void detectToken(Token *token);
			void detectInvalidToken(Token *token);
			//detected charaters
		    void detectWhiteSpace(SStream *&stream, char c);
		

			

		    

		};
	}
}

#endif