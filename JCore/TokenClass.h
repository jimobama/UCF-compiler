#ifndef TOKEN_CLASS_FILE_H
#define TOKEN_CLASS_FILE_H

#ifdef JCORE_EXPORTS
#define TOKEN_API __declspec(dllexport)
#else
#define TOKEN_API __declspec(dllexport)
#endif

#include "Comparable.h"
#include <string>
#include < stdint.h > 
namespace obaro
{
	namespace core
	{
		typedef enum TOKEN_API TokenClass
		{
			EOF_TOKEN = -1,
			INVALID_TOKEN, //start from minus -1
			IDENTIFIER,
			GROUP_STMT,
			LIFE_QUALIFIER,
			QUALIFIER,
			IMPORT_STMT,
			PRE_PROCESSOR,
			IF_STATEMENT,
			PACKAGE,
			CLASS,
			STRING,
			OPEN_QUOTE,
			SINGLE_QUOTE,
			SEMI_COLON,
			RETURN_STATEMENT,
			NEW_STATEMENT,
			TYPES,
			KEYWORD,
			DELIMITERS,
			SYMBOL,
			WHITE_SPACE,
			COMMENT_START,
			COMMENT_CLOSE,
			COMMA,
			CONST_NUMBER,
			STATEMENT_TERMINATOR,
			OPEN_BRACE,
			CLOSE_BRACE,
			OPEN_BRACKET,
			OPERATORS,
			CLOSE_BRACKET,
			ATSYMBOL
		};


		class Token :public Comparable<Token&>
		{
		public:
			std::string sequence;
			TokenClass type;
			int32_t lineNumber;
			int32_t columnNumber;
			//constructor
			Token()
			{
				this->columnNumber = 0;
				this->lineNumber = 0;
				this->type = TokenClass::INVALID_TOKEN;
				this->sequence = "";
			}
			TOKEN_API Token(TokenClass type, std::string sequece) :
				sequence(sequece), type(type)
			{
				this->columnNumber = 0;
				this->lineNumber = 0;
			}



			//@Override the comparable method
			TOKEN_API	bool compareTo(Token &cls)
			{
				if ((cls.sequence.compare(this->sequence) == 0) && (cls.type == this->type))
				{
					return true;
				}
				return false;
			}

		};

	}
}

#endif