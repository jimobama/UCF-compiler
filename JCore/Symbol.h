#ifndef SYMBOL_H
#define SYMBOL_H


#ifdef JCORE_EXPORTS
#define  SYMBOL_API __declspec(dllexport) 
#else
#define SYMBOL_API __declspec(dllimport) 
#endif
/*Comments
The symbol class objects

*/
#include "stdafx.h"
#include "Comparable.h"
#include <string>
#include <fstream>


namespace obaro
{

	namespace core
	{

		typedef enum SYMBOL_API symbol_type{
			ESCAPE = -1,
			NONE,
			LITERAL,
			OPERATOR
		};


		class Symbol :public Comparable < Symbol&>
		{
		private:
			char character;

		public:
			static const char EPSILON = (char)'\0';
			//Parameterised Contructor that accept a single character strings
			SYMBOL_API Symbol(char c);
			SYMBOL_API bool compareTo(Symbol &symbol);
			SYMBOL_API char getValue() const;
			char get_value()const;
			symbol_type type;


			//operator overloadding

			SYMBOL_API friend std::ostream& operator<<(std::ostream& out, const Symbol& symbol)
			{
				out << symbol.getValue();
				return out;
			}

			//The method append the symbol to the end of the string value
			SYMBOL_API	friend std::string& operator+(std::string &str, const Symbol &s)
			{
				str.push_back(s.getValue());
				return str;

			}

			SYMBOL_API	friend bool operator!=(const Symbol& s, char c)
			{
				if (c != s.getValue())
					return true;
				return false;
			}
			//The method append the symbol to the beginning of the string value
			SYMBOL_API 	friend std::string& operator+(const Symbol &s, std::string &str)
			{
				std::string vstr = "";
				vstr = (vstr + s);
				//append it to the end of the string
				str = vstr + str;
				return str;
			}//end method

			// join the symbol character together
			SYMBOL_API	std::string operator+(Symbol & symbol)
			{
				std::string str = "";
				str = str + *this;
				str = str + symbol;
				return str;
			}

		};

	}//end the core namespace brace
}//end obaro namespace brace




#endif