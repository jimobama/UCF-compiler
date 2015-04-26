#include "stdafx.h"
#include "SStream.h"
#include <exception>
using namespace obaro::core;



/*comment

*/
Symbol::Symbol(char c) :Comparable()
{
	this->character = (char)c;
	type = symbol_type::NONE;
};

/*comment

*/
char Symbol::getValue() const
{

  return  character;
	
}

/*Comment */
bool Symbol::compareTo(Symbol &symbol)
{
	if (symbol.getValue() != this->getValue())
		return false;
	return true;
}

char Symbol::get_value() const
{
	return this->getValue();
}