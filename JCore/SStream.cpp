#include "stdafx.h"
#include "SStream.h"



using namespace obaro::core;


SStream::SStream() :Comparable()
{

	this->init("");
}


SStream::SStream(std::string characters) :Comparable()
{
	if (!characters.empty())
	   this->init(characters);

}

/*comment
*/

SStream::SStream(const char* characters) :Comparable()
{
	this->init(characters);
}


int const SStream::size()
{
	return this->symbols.size();
}

/*comments
*/

bool SStream::compareTo(SStream& classDerive)
{
	if (this->symbols.size() == classDerive.size())
	{
		//check if element make matches in order of arrangements
		return true;
	}
	return false;
}


/*comment

*/

const  Symbol* SStream::current()
{
	Symbol* s = new Symbol('\0');

	if (!this->isEOF())
	{
		s = this->symbols.at(index_position);
	}
	return s;
}


/*comment */

void SStream::advance(int32_t n)
{
	index_position += n;
}


/*comment */

void SStream::seekp(int32_t n)
{
	if (n < 0)
		n = 0;
	else if (n >= (int32_t) this->symbols.size())
	{

		n = (int32_t) this->symbols.size();
	}
	//set the value
	this->index_position = n;
}


/*comment */

Symbol *SStream::peek(int32_t n)
{

	int32_t ahead = (int32_t)((int32_t)(index_position)) + n;

	if (ahead > (int32_t)(this->symbols.size() - 1))
	{
		//return end of file character
		return  new Symbol('\0');
	}
	else if (ahead < 0)
	{
		ahead = 0;
	}
	// now return the position

	return this->symbols.at(ahead);
}


/*comment
*/

bool SStream::hasNext()
{
	int32_t index = this->index_position;
	int32_t size = this->symbols.size();

	if (index < (size))
		return true;
	return false;
}

/*comment
*/

Symbol *SStream::behind(int n)
{
	if (this->symbols.size() <= 0)
		return new Symbol('\0');

	int index_position = this->index_position - n;

	if (index_position < 0)
		return new Symbol('\0');

	return this->symbols.at(index_position);


}


void SStream::moveAhead(const Symbol * s)
{
	if (!this->isEOF())
	{
		//move ahead to the symbol , from the current position
		Symbol *current = (Symbol*) this->current();
		while (current->compareTo((Symbol)*s) != true)
		{
			current = (Symbol*)this->current();
		}
	}
}
/*comment

*/

bool SStream::isEOF()
{
	int32_t index = this->index_position;
	int32_t size = this->symbols.size();

	if (index >= (size))
		return true;
	return false;
}


/*Comments

*/

void SStream::init(std::string str)
{

	std::string::iterator iter = str.begin();
	this->index_position = 0;
	for (iter; iter != str.end(); iter++)
	{
		char c = *iter;
		Symbol *s = new Symbol((char)c);
		this->symbols.push_back(s);

	}

}

/*comments*/

std::string	SStream::toString()
{
	std::string result = "";
	std::vector<Symbol*>::iterator iter = this->symbols.begin();
	//iterate
	while (iter != symbols.end())
	{
		result.push_back((*iter)->getValue());
		iter++;
	}
	//return the result;

	return result;
}


int32_t SStream::getCurrentIndex()
{
	return this->index_position;
}

void SStream::replaceSymbol(int index, Symbol *s)
{
	if (index >= 0 && index < (int)this->symbols.size())
	{

		this->symbols[index] = s;

	}

}

/*Delete the character types and reset the pointer to the begin*/

void SStream::deleteAll(symbol_type type)
{
	std::vector<Symbol*>::iterator iter = this->symbols.begin();

	for (iter; iter != this->symbols.end(); iter++)
	{
		Symbol *symbol = *iter;
		if (symbol->type == type)
		{
			iter = this->symbols.erase(iter);
		}
	}
	this->index_position = 0;


}


void SStream::pushBack(const  Symbol *s)
{
	this->symbols.push_back((Symbol*)s);

}


SStream::~SStream()
{


}