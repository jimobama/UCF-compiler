#include "stdafx.h"
#include "ILexicalListener.h"
#include "LexicalAnalyser.h"
#include <lexicalanalyserexception.h>
#include <State.h>
#include <stateType.h>
#include <TokenClass.h>
#include <IGraph.h>
#include <DFAGraph.h>

using namespace obaro::core;
using namespace obaro::lexical;
using namespace obaro::graphs;

ILexicalListener::ILexicalListener(LexicalAnalyser *analyser)
{
	
	this->attach(analyser);
}


void ILexicalListener::attach(LexicalAnalyser *analyser)
{
	this->__analyser = (LexicalAnalyser*)analyser;
}

//Parser the white and set the current token after the white space
void ILexicalListener::detectWhiteSpace(SStream *&stream,char c)
{
	if (this->__analyser->isWhiteSpace(c))
	{
		this->__analyser->countLine(c);
		stream->advance();		
		detectWhiteSpace(stream, stream->current()->getValue());		
	}
	
}



void ILexicalListener::detectToken(Token *token)
{
	if (token != NULL && token->type == graphs::StateType::FINAL_STATE)
	{
		this->__analyser->xhsSetCurrentToken(token);
		this->__analyser->xhsResetSimulator();
	}
	this->detectInvalidToken(token);
}

void ILexicalListener::detectInvalidToken(Token *token)
{
	if (token != NULL && token->type != StateType::FINAL_STATE)
	{
		 //emit error message on token
		this->__analyser->emitMessage(token, "Invalid token found at ");
		return;
	}
	//if is end of file
	if (!__analyser->hasNextToken())
	{
		token =new  Token();
		token->type = TokenClass::EOF_TOKEN;
		this->__analyser->xhsSetCurrentToken(token);
	}

	this->__analyser->xhsResetSimulator();
}
bool  ILexicalListener::isNormalInput(char b, char c)
{
	if (b != '\\' && c == '\"')
	{		
		return false;
	}
	else
	{
		return true;
	}

}

Token * ILexicalListener::detectAcceptState(DFAGraph* g, SStream *&stream, State* state)
{

	DFAGraph *graph = (DFAGraph*) g;

	Token * newToken = NULL;
	newToken = new Token();
	if (state != NULL)
	{
		newToken->type = state->tokenID;
		//set the currrent accepting state
		if (state->state ==StateType::FINAL_STATE)
		{
		 	this->__analyser->xhsAcceptingState(state);
		
		}

		//longest token
		if (stream->hasNext())
		{
			stream->advance();
			char c = stream->current()->getValue();
			State * next = graph->delta(state, c);
			
			if (next != NULL)
			{				
				this->__analyser->xhsInsertChar(c);
				newToken =  this->detectAcceptState(graph, stream, next);
			}
		}

	}

	  
	//emit state
	return newToken;
	
}