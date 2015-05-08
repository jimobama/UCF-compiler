// LexicalAnalyser.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "LexicalAnalyser.h"
#include "ILexicalListener.h"
#include <lexicalanalyserexception.h>
#include "GrammarLexeme.h"
#include <stateType.h>
#include <Node.h>
#include <FileInputStream.h>

using namespace obaro;
using namespace obaro::lexical;
using namespace obaro::io;

LexicalAnalyser::LexicalAnalyser(bool abool)
{
	this->init(abool);
}
LexicalAnalyser::LexicalAnalyser(FileInputStream *stream,bool abool)
{
	
	this->init(abool);	
	this->setSource(stream);
	
	
}

void LexicalAnalyser::init(bool abool)
{
	this->setListener(new ILexicalListener(this));
	this->useSpecificationFromFile = abool;
	this->__filestream = NULL;
	this->__symbolStream = NULL;
	currentAcceptingState = NULL;
	__isPrepared = false;
	this->__columnNumber = 0;
	this->__currentToken = NULL;
	this->__lineNumber = 0;
	this->__lexemes = new GrammarLexeme(this->useSpecificationFromFile);
}
void LexicalAnalyser::setSource(io::FileInputStream *stream)
{

	this->__filestream = stream;
	std::string sources = this->__filestream->GetContext();
	this->__symbolStream = new SStream(sources);

}
void LexicalAnalyser::prepare()
{
	
	if (!__isPrepared)
	{	
		std::wstring filename = L"lspec.xml";
		if (!this->useSpecificationFromFile)
		{
			this->__lexemes->useDefault();
			this->dfaGraph = this->__lexemes->combine();			
			DFAGraph::saveTo(this->dfaGraph , filename);
		}
		else
		{
			this->dfaGraph = (DFAGraph*) DFAGraph::loadXMLGraph(filename);
		}
		
			
		this->__isPrepared = true;
		/*
		
		*/
		
	}

	
}
//The method scan the input source code and return the first detected tokens
Token *LexicalAnalyser::parserNextToken()
{
	Token *token = new Token(TokenClass::INVALID_TOKEN,"");
	if (!this->__isPrepared)
	{
	    std::cerr << "Lexical error: prepare method must be called to initial the system before any other method can be called.\n";
		return NULL;
	}	
	//start State
	if (this->__symbolStream->size() > 0)
	{

		State * state = (State*)this->xhsGetSimulator()->getInitial();
		if (state != NULL)
		{
			token =	__parserToken(state, this->__symbolStream->current()->getValue());
		}
	}
	//set the current token
	this->xhsSetCurrentToken(token);
	return token;

}

//isComment

bool  LexicalAnalyser::isComment(char c)
{
	if (c == '/' &&  this->__symbolStream->peek()->getValue() == '/')
	{
		return true;
	}
	return false;

}
//token parser

Token *LexicalAnalyser::__parserToken(State*  state, char c)
{
	if (!this->__symbolStream->hasNext())
	{
		return NULL;
	}
	Token *token = NULL;
	this->countLine(c);
	if (this->isWhiteSpace(c))
	{		
		this->__lexicalListener->detectWhiteSpace(this->__symbolStream, c);
	    token = this->__parserToken(state, this->__symbolStream->current()->getValue());
	
	}
	else if (this->isComment(c))
	{
		this->skipUntil('\n');
		
		token = this->__parserToken(state, this->__symbolStream->current()->getValue());
	}
	else{
		
			if (this->isDoubleQuotes(c))
			{
				token = this->__parserString(c);
			}
			else{
				token = this->parserTokenStates(state, c);
			}
		
	}
	
	return token;

}

Token * LexicalAnalyser::parserTokenStates(State *state, char c)
{
	
	Token *token = NULL;
	
	State * next = this->dfaGraph->delta(state, c);
	
	
		
	while (this->__symbolStream->hasNext() && next != NULL)
	{
		this->__pattern.push_back(c);
		switch (next->state)
		{
			case StateType::FINAL_STATE:
			{
				this->currentAcceptingState = next;
				break;
			}
			default:
				break;
		    
		}
		
		this->__symbolStream->advance();
		c = this->__symbolStream->current()->getValue();		
		state = next;
		next = this->dfaGraph->delta(state, c);
	}
	

	if (this->currentAcceptingState == NULL)
	{
		if (next != NULL)
		{
			token = new Token(TokenClass::INVALID_TOKEN, this->__pattern);
			token->columnNumber = this->__columnNumber;
			token->lineNumber = this->__lineNumber;			
		}
		else
		{
			if (((int)c) != -52)
			{
				std::string strc("");
				strc.push_back(c);
				std::string msgerror = "Invalid character (" + strc;
				this->emitMessage(NULL, msgerror + ") token found at ");
			}
		}
	}
	else{
		token = new Token(this->currentAcceptingState->tokenID, this->__pattern);
		token->columnNumber = this->__columnNumber;
		token->lineNumber = this->__lineNumber;
	}
	
	this->xhsResetSimulator();
	return token;
}

Token * LexicalAnalyser::__parserString(char c)
{

	std::string values = "";
	std::cout << " \nstarts:  " << c;
	this->__symbolStream->advance();
	char cw = this->__symbolStream->current()->getValue();

	while (!this->isDoubleQuotes(cw))
	{		
		
		std::cout << " \nQuotes:  " << cw;
		values.push_back(cw);
		if (!this->__symbolStream->hasNext())
		{
			break;
		}
		else{
			this->__symbolStream->advance();
			cw = this->__symbolStream->current()->getValue();
		}
	} 
	
	std::cout << " \nends:  " << cw<<"\n";
	this->__symbolStream->advance();
   //token current
   Token *token = new Token(TokenClass::STRING,values);
   token->lineNumber = this->__lineNumber;
   token->columnNumber = this->__columnNumber;
   if (cw != '"')
   {
	   std::cout << cw;
	   this->emitMessage(token, "\nMissing double quotes for string value at ");
   }
	 
   return token;
}

//check if the character is white space

bool LexicalAnalyser::isWhiteSpace(char c)
{

	switch (c)
	{
	case ' ':
	case '\n':
	case '\r':
	case '\t':
	
		return true;
	default:
		return false;
	}

}

void LexicalAnalyser::skipUntil(char c)
{
   if  (this->__symbolStream->hasNext())
	{
		if (c != this->__symbolStream->current()->getValue())
		{
			this->__symbolStream->advance();
			skipUntil(c);
		}
		else
		{
			this->countLine(c);
		}
	}	
}

bool LexicalAnalyser::isDoubleQuotes(char c)
{
	switch (c)
	{
	case '"':	
		return true;
	default:
		return false;
	}
}

void LexicalAnalyser::xhsSetCurrentToken(Token *t)
{
	this->__currentToken = t;
}

void LexicalAnalyser::xhsResetSimulator()
{
	this->__pattern = "";
	this->currentAcceptingState = NULL;
	

}

void LexicalAnalyser::xhsInsertChar(char c)
{
	this->__pattern.push_back(c);
}

void LexicalAnalyser::emitMessage(Token* t,std::string msg)
{
	if (t != NULL){
		t->lineNumber = this->__lineNumber;
		t->columnNumber = this->__columnNumber;
		t->sequence = this->__pattern.c_str();
	}
	
	std::cerr << msg << " line : " << this->__lineNumber << ", column : " << this->__columnNumber << std::endl;
}

bool LexicalAnalyser::hasNextToken()
{
	if (this->__symbolStream->hasNext())
	{
		return true;
	}
	return false;
}
Token * LexicalAnalyser::xhsGetCurrentToken()
{
	return this->__currentToken;
}
void LexicalAnalyser::xhsAcceptingState(State* accepting)
{
	this->currentAcceptingState = accepting;
}

void LexicalAnalyser::countLine(char c)
{
	if (c == '\n')
	{
		this->__columnNumber = 0;
		this->__lineNumber++;
	}else
	this->__columnNumber++;
}
void LexicalAnalyser::removeListener()
{
	this->__lexicalListener = NULL;
}
void LexicalAnalyser::setListener(ILexicalListener *listener)
{
	this->__lexicalListener = listener;
}

DFAGraph *LexicalAnalyser::xhsGetSimulator()
{
	if (this->dfaGraph == NULL)
	{
		this->dfaGraph = new DFAGraph(new State(1));

	}
	return this->dfaGraph;
}
LexicalAnalyser::~LexicalAnalyser()
{
    this->removeListener();
	delete this->__lexemes;
	delete this->dfaGraph;
	delete this->__symbolStream;
	if (this->currentAcceptingState != NULL){
		delete this->currentAcceptingState;
	}
	if (this->__filestream !=NULL)
		delete this->__filestream;
	
}

