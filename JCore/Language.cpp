#include "stdafx.h"
#include "language.h"
#include <stack>
#include <iostream>
#include "lexicalanalyserexception.h"
#include "InfixExpression.h"
#include "SStream.h"
#include "Symbol.h"


using namespace obaro::core;
using namespace obaro;


Language::Language(std::string const regex)
{
	//covert the raw data into a character symbol
	this->stream = new SStream(regex);
	this->infix_ex_parser = new obaro::core::InfixExpression();
	this->parser();
	
	
}

void  Language::parser()
{
	
	
	if (this->is_bracket_formatted())
	{
		
		//prepare the symbols 
		this->prepare_symbols();
		//		
		*stream = this->expandConcatenation(*stream);
		this->infix_ex_parser->setStream(stream);
		//parser the infix expression to postfix that can be understand and evaluated by the computer
		this->infix_ex_parser->parser();
		//we are done with this variable delete it	
		*(this->stream) = this->infix_ex_parser->toStream();
		
	}
	else
	{
		//output the error 
		std::cerr << " Error invalid regular expression  close or open bracket missing\n";
		
	}
	

}

bool Language::is_bracket_formatted()
{
	//if there is no character then return  true
	if (this->stream->size() == 0)
		return true;
	stream->seekp(0);//reposition to the begin of the text	
	return parser_bracket();
}

/*Parser the brackets
*/
bool  Language::parser_bracket()
{
	std::stack<Symbol*> *stack;
	//create the interface of the class					
	stack = new std::stack<Symbol*>();
	int counter = 0;
	while (stream->hasNext())
	{
		Symbol *current =(Symbol*) stream->current();
		Symbol *behind = stream->behind();
		//advance the pointer one ahead to the next input symbol
		stream->advance();

		//check if the input symbol is open_bracket
		if (this->is_open_bracket(behind, current))
		{
			//push in the symbol
			stack->push(current);
			counter++;

		}//check if its a close bracket then pop out
		else if (this->is_close_bracket(behind, current))
		{
			if (!stack->empty())
			{
				//start matching check
				switch (current->getValue())
				{
				case ')':
					//check if the top of the stack is same with the opposite
					if (stack->top()->getValue() == '('){
						stack->pop();
						counter--;
					}
					break;
				case '}':
					if (stack->top()->getValue() == '{'){
						stack->pop();
						counter--;
					}
					break;
				case ']':
					if (stack->top()->getValue() == '['){
						stack->pop();
						counter--;
					}
					break;
				default:
					break;
				}
			}//end if


		}


	}//end while

	if (std::abs(counter) == 0)
		return true;
	return false;
}


bool Language::is_input(Symbol  *behind, Symbol   *current)
{
	char b = behind->getValue();
	char c = current->getValue();
	bool okay = false;
	if (!this->infix_ex_parser->isOperator(current) &&
		!this->infix_ex_parser->isCloseBracket(current) &&
		!this->infix_ex_parser->isOpenBracket(current))
	{
		okay = true;
	}
	return okay;
}

bool  Language::is_used_as_escape(Symbol  *behind, Symbol   *current)
{
	char b = behind->get_value();
	char c = current->get_value();
	bool okay = false;
	if (b == '\\' && (infix_ex_parser->isOperator(current) ||
		infix_ex_parser->isCloseBracket(current) ||
		infix_ex_parser->isOpenBracket(current)))
	{
		okay = true;
	}
	return okay;
}

bool Language::is_close_bracket(Symbol  *behind, Symbol  *current)
{
	char b = behind->get_value();
	char c = current->get_value();
	//check if the chracter is a ) or } or ] provided the behind character is not an escape character
	if (b != '\\' &&  this->infix_ex_parser->isCloseBracket(current))
	{

		return true;
	}
	return false;
}

bool Language::is_open_bracket(Symbol  *behind, Symbol  *current)
{
	char b = behind->get_value();
	char c = current->get_value();

	if (b != '\\' && this->infix_ex_parser->isOpenBracket(current))
	{

		return true;
	}
	return false;
}


bool Language::is_operator(Symbol *behind, Symbol  *current)
{
	char b = behind->get_value();
	char c = current->get_value();

	if (b != '\\' &&  this->infix_ex_parser->isOperator(current))
	{
		return true;
	}
	return false;
}


/*
Comment
Assign the characters types ,
*/

void Language::prepare_symbols()
{
	//return pointer back to the starting of the stream
	this->stream->seekp(0);


	while (this->stream->hasNext())
	{
		Symbol *behind = this->stream->behind();
		Symbol *current =(Symbol*) this->stream->current();
		Symbol *peek = this->stream->peek();

		// if is an escape character
		if (current->get_value() == '\\')
		{
			//detected and modifiers an escape simple type
			this->detect_escape_symbols(current, peek);
		}
		else if (this->is_operator(behind, current))
		{

			current->type = symbol_type::OPERATOR;
			this->stream->replaceSymbol(this->stream->getCurrentIndex(), current);
			//std::cout << current;
		}
		else if (this->is_input(behind, current))
		{

			current->type = symbol_type::LITERAL;
			this->stream->replaceSymbol(this->stream->getCurrentIndex(), current);
			//std::cout << current;
		}

		this->stream->advance();
	}
	//clear and prepare symbol stream for real parsering
	this->stream->deleteAll(symbol_type::ESCAPE);

}

/*
*/

void Language::detect_escape_symbols(Symbol *current, Symbol *peek)
{
	// then look ahead
	if (infix_ex_parser->isCloseBracket(peek) ||
		infix_ex_parser->isOpenBracket(peek) ||
		infix_ex_parser->isOperator(peek))
	{
		//this is an escape character
		peek->type = symbol_type::LITERAL;
		this->stream->replaceSymbol(this->stream->getCurrentIndex() + 1, peek);
		current->type = symbol_type::ESCAPE;
		this->stream->replaceSymbol(this->stream->getCurrentIndex(), current);
		//std::cout << peek;
	}
	else
	{
		current->type = symbol_type::LITERAL;
		this->stream->replaceSymbol(this->stream->getCurrentIndex(),current);
		//std::cout << current;
	}
}

SStream *Language::toStream()
{
	if (this->stream ==NULL)
	{
		this->stream = new SStream("");
	}
	return (this->stream);
}





/*Comment
The method takes two arguments
start: a start value range can be any character from 0-9 or a-z A-Z
end:  a end value range can be any of the character from 0-9,a-zA-Z
*/
std::string Language::makeRange(char start, char end)
{
	std::string range = "";
	int initial = (int)start;
	int final = (int)end;

	if (start >= '0' && end <= '9')
	{
		range = get_range(initial, final);
	}
	else if (start >= 'a' && end <= 'z')
	{
		//it is a range for small case letter
		range = get_range(initial, final);
	}
	else if (start >= 'A' && end <= 'Z')
	{
		range = get_range(initial, final);
	}
	else{ range.push_back((char)0); }
	return range;
}//end method 

//The method is the re-factory part of the makeRange
std::string Language::get_range(int initial, int final)
{
	std::string range = "";
	//the loop
	while (initial < final)
	{
		range.push_back((char)initial);
		range += REGEX_CONST::UNION;
		initial++;
	}
	range.push_back((char)initial);
	//return it back 
	return range;
}//end method


/*
The function will expand the concatenation operations that are hidden and replace with the dot
*/

SStream Language::expandConcatenation(SStream &c_stream)
{
	//reset the position back to the start of the characters		
	SStream result;

	while (c_stream.hasNext())
	{
	    Symbol *behind = c_stream.behind();
		Symbol *current =(Symbol*) c_stream.current();
		Symbol *peek = c_stream.peek();


		if (current->type == symbol_type::LITERAL && !peek->compareTo(Symbol('\0')))
		{
			if (peek->type == symbol_type::LITERAL || (peek->type == symbol_type::NONE && this->infix_ex_parser->isOpenBracket(peek)))
			{
				result.pushBack(current);
				//create contenation symbol
				Symbol *concat= new Symbol(REGEX_CONST::CONCATENATION);
				concat->type = symbol_type::OPERATOR;
				result.pushBack(concat);
			}
			else
			{
				result.pushBack(current);
			}


		}
		else if (current->type == symbol_type::OPERATOR  &&  this->infix_ex_parser->isCloseBracket(behind))
		{
			if (peek->type == symbol_type::LITERAL || (peek->type == symbol_type::NONE && this->infix_ex_parser->isOpenBracket(peek)))
			{
				result.pushBack(current);
				//create contenation symbol
				Symbol *concat= new Symbol(REGEX_CONST::CONCATENATION);
				concat->type = symbol_type::OPERATOR;
				result.pushBack(concat);
			}
			else
			{
				result.pushBack(current);
			}
		}
		else
		{
			result.pushBack(current);
		}

		c_stream.advance();
	}//end while

	return result;

}
