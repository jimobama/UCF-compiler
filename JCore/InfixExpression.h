#ifndef INFIX_EXPRESSION_H
#define INFIX_EXPRESSION_H

#ifdef JCORE_EXPORTS
#define INFIX_EXPRESSION_API __declspec(dllexport)
#else
#define INFIX_EXPRESSION_API __declspec(dllimport)
#endif


#include <stack>
#include <string>
#include <regex>
namespace obaro
{
	namespace core
	{
		class SStream;
		class Symbol;

		// regular expression operators
		typedef struct INFIX_EXPRESSION_API
		{	//The kleene star indicates there is zero or more of the preceding element
			static const char KLEENE_STAR = '*';
			static const char CONCATENATION = '.';
			static const char UNION = '|';
			static const char PLUS = '+';
			static const char QUESTION_MARK = '?';
		}REGEX_CONST;


		class InfixExpression
		{
			/*The private fields properties*/
		private:
			SStream *input_stream;
			std::stack<Symbol*>	  op_stack; //the operator stacks
			std::stack<Symbol*>	  input_stack;//the result postfix stacks

		public:
			//constructors
			InfixExpression();
			InfixExpression(SStream * );
			virtual	~InfixExpression();
			INFIX_EXPRESSION_API SStream		toStream();
			INFIX_EXPRESSION_API bool						isOperator(Symbol  const *op);
			INFIX_EXPRESSION_API int						opPriority(char c);
			INFIX_EXPRESSION_API bool						isOpenBracket(Symbol  *b);
			INFIX_EXPRESSION_API bool						isCloseBracket(Symbol  *b);
			INFIX_EXPRESSION_API void						setStream(SStream*);
			INFIX_EXPRESSION_API void						parser();

		private:
			void						orderOperators(Symbol *op);
			void						evaluateBracket();
			void						initilised(SStream *);
			void						evaluateCompletion();


		};
	}
}


#endif