#ifndef JLEXICALANLALYSEREXCEPTION_H
#define  JLEXICALANLALYSEREXCEPTION_H

#ifdef JCORE_EXPORTS
#define JLEXICALANLALYSEREXCEPTION_API __declspec(dllexport)
#else
#define JLEXICALANLALYSEREXCEPTION_API __declspec(dllimport)
#endif

#include<string>
#include<exception>

namespace obaro
{
	namespace core
	{

		class LexicalAnalyserException :public std::exception
		{
		private:
			char code;
			const std::string message;
		public:
			//The exception class take the error message and the error code in char.
			JLEXICALANLALYSEREXCEPTION_API 	LexicalAnalyserException(std::string message, char code = (char)0x000) :std::exception(message.c_str()),
				message(message.c_str()), code(code)
			{

			}
		public:
			JLEXICALANLALYSEREXCEPTION_API  const char* what() const throw()
			{
				return this->message.c_str();
			}
			JLEXICALANLALYSEREXCEPTION_API 	char getCode()
			{
				return code;
			}




		};//end class

	}
}

#endif