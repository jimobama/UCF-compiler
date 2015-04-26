#include "stdafx.h"
#include "InfixExpression.h"
#include "lexicalanalyserexception.h"
#include "SStream.h"
#include "Symbol.h"
using namespace obaro::core;

/*Comments
*/
InfixExpression::InfixExpression()
{
	
	this->initilised( new SStream());
}
InfixExpression::InfixExpression(SStream *stream)
{
	this->initilised(stream);
}

void InfixExpression::setStream(SStream *stream)
{
	input_stream = stream;
}

/*Comment
Initialised the variables
*/
void InfixExpression::initilised(SStream *stream)
{
	input_stream = stream;
}

/*Comments

*/
bool InfixExpression::isCloseBracket(Symbol  *b)
{
	const char c = b->getValue();

	if (c == '}' || c == ']' || c == ')')
		return true;
	return false;

}
/*Comments

*/
bool InfixExpression::isOpenBracket(Symbol  *b)
{
	const char c = b->getValue();
	if (c == '{' || c == '(' || c == '[')
		return true;
	return false;
}

void InfixExpression::parser()
{
	
	//Check if the string is empty
	if (input_stream == NULL || input_stream->size() == 0)
		return;
	

	this->input_stream->seekp(0);
	while (input_stream->hasNext())
	{
		
		Symbol *current = NULL;
		current =(Symbol*) this->input_stream->current();

		if (current->type == symbol_type::OPERATOR && this->isOperator(current))
		{

			if (!this->op_stack.empty())
			{

				this->orderOperators(current);
			}
			else
			{

				this->op_stack.push(current);

			}
		}
		else if (current->type == symbol_type::NONE && this->isOpenBracket(current))
		{

			this->op_stack.push(current);

		}
		else if (current->type == symbol_type::NONE  && this->isCloseBracket(current))
		{

			this->evaluateBracket();
		}
		else
		{

			// push only literal characters only
			if (current->type == symbol_type::LITERAL){

				this->input_stack.push(current);
			}
		}
		//advance input pointer
		this->input_stream->advance();
	}
	//pop all the operators outs
	this->evaluateCompletion();




}
/*
The method complete the parsing process, to make such there is no operator left in the stack
*/
void InfixExpression::evaluateCompletion()
{
	while (!this->op_stack.empty())
	{
		Symbol *c = op_stack.top();
		this->op_stack.pop();
		this->input_stack.push(c);
	}
}

/*The method evaluate expression in brackets
*/
void InfixExpression::evaluateBracket()
{


	while (!this->op_stack.empty())
	{
		Symbol *op_s = this->op_stack.top();
		this->op_stack.pop();
		if (this->isOpenBracket(op_s))
			break;
		this->input_stack.push(op_s);

	}

}
/*Comments
Keep operator expression in order of precedences
*/
void InfixExpression::orderOperators(Symbol *op)
{
	//pop out all the higher op_stack operator that are higher or equal to the priority of *iter
	while (!this->op_stack.empty())
	{
		if (this->isOpenBracket(this->op_stack.top()))
		{
			this->op_stack.push((Symbol*)op);
			break;
		}
		else{
			if (this->opPriority(op->getValue()) > this->opPriority(this->op_stack.top()->getValue()))
			{
				//if the top stack op have lower priority then just push the operator into the stack
				this->op_stack.push(op);
				break;
			}
			else if (this->opPriority(this->op_stack.top()->getValue()) >= this->opPriority(op->getValue()))
			{
				// order the operator
				Symbol *c = this->op_stack.top();
				this->op_stack.pop();
				this->input_stack.push(c);
				if (this->op_stack.empty())
				{
					this->op_stack.push(op);
					break;
				}

			}
		}


	}//end while statement
}


/*Comments

*/
bool InfixExpression::isOperator(Symbol  const *c)
{
	if (c->getValue() == REGEX_CONST::KLEENE_STAR ||
		c->getValue() == REGEX_CONST::UNION ||
		c->getValue() == REGEX_CONST::PLUS ||
		c->getValue() == REGEX_CONST::CONCATENATION)
		return true;
	return false;
}
/*Comments

*/
int InfixExpression::opPriority(char c)
{
	//return the ranking of the regular expression operator
	switch (c)
	{
		//repetition
	case REGEX_CONST::KLEENE_STAR:
	case REGEX_CONST::PLUS:
		return 2;
	case REGEX_CONST::UNION:
	case REGEX_CONST::CONCATENATION:
	default:
		return 1;

	}
}

/*Comments

*/
SStream InfixExpression::toStream()
{


	SStream streams;
	//pop and push the literal value into the op_stack


	while (!this->input_stack.empty())
	{
		Symbol *c = this->input_stack.top();
		this->input_stack.pop();
		this->op_stack.push(c);
		//std::cout << "Starting Infix Parsing\n";
	}

	// now convert it to string
	while (!this->op_stack.empty())
	{
		Symbol *c = this->op_stack.top();
		this->op_stack.pop();
		streams.pushBack(c);

	}


	return streams;
}


/*Comments

*/
InfixExpression::~InfixExpression()
{

	delete input_stream;

}
