
#ifndef LANGUAGE_CORE_H
#define LANGUAGE_CORE_H

#ifdef JCORE_EXPORTS
#define  EXPORT_LANGUAGE_API __declspec(dllexport)
#else
#define  EXPORT_LANGUAGE_API __declspec(dllimport)
#endif


#include <string>




namespace obaro
{
	namespace core
	{
		class SStream;
		class Symbol;
		class InfixExpression;

		//inherit the 
		class Language 
		{
		private:
			//fields
			SStream   *stream;
			InfixExpression *infix_ex_parser;
			//methods
		private:
			bool		  is_bracket_formatted();
			bool          parser_bracket();
			bool			 is_input(Symbol  *, Symbol   *);
			bool			 is_close_bracket(Symbol  *, Symbol  *);
			bool			 is_open_bracket(Symbol  *, Symbol  *);
			bool			 is_operator(Symbol  *, Symbol  *);
			void          prepare_symbols();
			bool          is_used_as_escape(Symbol *, Symbol  *);
			SStream  expandConcatenation(SStream  &);
			static EXPORT_LANGUAGE_API std::string		 get_range(int initial, int final);
			void detect_escape_symbols(Symbol *current, Symbol *peek);
		protected:
			
		 void parser();
		public:
			EXPORT_LANGUAGE_API Language(const std::string regexpr="");
			EXPORT_LANGUAGE_API  SStream *toStream();
			static EXPORT_LANGUAGE_API  std::string	 makeRange(char start, char end);
			


		};
	}
}

#endif