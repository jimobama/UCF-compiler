#include "stdafx.h"
#include "GrammarLexeme.h"
#include "Language.h"
#include <DFAGraph.h>
#include <State.h>
#include <Transition.h>




using namespace obaro::graphs;
using namespace obaro::lexical;

GrammarLexeme *GrammarLexeme::__instance = NULL;
std::string GrammarLexeme::DIGIT = (Language::makeRange('0', '9'));
std::string GrammarLexeme::LOWERCASE = (Language::makeRange('a', 'z'));
std::string GrammarLexeme::UPPERCASE = Language::makeRange('A', 'Z');
std::string GrammarLexeme::INTEGER = "(" + DIGIT + ")+";
std::string GrammarLexeme::DOUBLE = ("((" + GrammarLexeme::INTEGER + ")*\\.(" + GrammarLexeme::INTEGER + ")*)");
std::string GrammarLexeme::NUMBER = "(("+ DOUBLE + ")|" + GrammarLexeme::INTEGER+")";
std::string GrammarLexeme::ALPHABET = GrammarLexeme::LOWERCASE + "|" + GrammarLexeme::UPPERCASE;
std::string GrammarLexeme::ALPH_NUMERIC = GrammarLexeme::ALPHABET + "|" + GrammarLexeme::DIGIT;
std::string GrammarLexeme::WORD = "(" + GrammarLexeme::ALPHABET + "|_)+" + "((" + GrammarLexeme::ALPH_NUMERIC + ")*)";
std::string GrammarLexeme::WHITE_SPACES = "(\t| |\r|\n)";
std::string GrammarLexeme::SPECIAL_CHARACTERS = "`|!|=|$|%|&|£";


//Constructor
GrammarLexeme::GrammarLexeme(bool loadfromdisk)
{
	this->IsLoadFromDisk = loadfromdisk;
	this->__nfa.clear();

}

void GrammarLexeme::initalised()
{

	this->newLexicon("if", TokenClass::KEYWORD);
	this->newLexicon("else", TokenClass::KEYWORD);
	this->newLexicon("import", TokenClass::KEYWORD);
	this->newLexicon("\"", TokenClass::STRING);
	this->newLexicon("void", TokenClass::KEYWORD);
	this->newLexicon("class", TokenClass::KEYWORD);
    this->newLexicon("public", TokenClass::KEYWORD);
	this->newLexicon("private", TokenClass::KEYWORD);
	this->newLexicon("\\\\", TokenClass::COMMENT_START);

 	this->newLexicon("int", TokenClass::KEYWORD);
	this->newLexicon("::", TokenClass::SEMI_COLON);
	//this->newLexicon(WORD, TokenClass::IDENTIFIER);
	this->newLexicon(";", TokenClass::COMMA);
	this->newLexicon("\\}", TokenClass::CLOSE_BRACE);
	this->newLexicon("\\{", TokenClass::OPEN_BRACE);
	this->newLexicon("\\(", TokenClass::OPEN_BRACKET);
	this->newLexicon("\\)", TokenClass::CLOSE_BRACKET);
	//operators
	this->newLexicon("=", TokenClass::OPERATORS);
	this->newLexicon("\\*", TokenClass::OPERATORS);
	this->newLexicon("-", TokenClass::OPERATORS);
	this->newLexicon("\\+", TokenClass::OPERATORS);
	this->newLexicon("<", TokenClass::OPERATORS);
	this->newLexicon(">", TokenClass::OPERATORS);
	this->newLexicon("<=", TokenClass::OPERATORS);
	this->newLexicon(">=", TokenClass::OPERATORS);
	this->newLexicon("!", TokenClass::OPERATORS);
	this->newLexicon("==", TokenClass::OPERATORS);


	this->newLexicon("class", TokenClass::KEYWORD);
	this->newLexicon("public", TokenClass::KEYWORD);
	//this->newLexicon(NUMBER, TokenClass::CONST_NUMBER);
}



void GrammarLexeme::newLexicon(std::string regex, obaro::core::TokenClass id)
{
	if (regex.length() > 0){
		NFAGraph *machine = new  NFAGraph(new Language(regex), id);
		machine->compile();	
	
		this->__nfa.push_back(machine);
	}
}

//combination of the non-deterministic finite state machine
/*
   let A = first NFA
   let B  = second NFA
   let C = third NFA

   if A->start = start Node
   and son with B and C 
   to combine the three NFA machine 

   New Start node will be created for the NFA D
   D = D->start link to B->start 
       D->start link to C->start
	   D-> start link to A-start


*/
DFAGraph *GrammarLexeme::combine()
{
	DFAGraph * dfa = new DFAGraph();
    
	State* link = new State(0);

	if (!this->IsLoadFromDisk)
	{
		NFAGraph *result = new NFAGraph();
		std::vector<NFAGraph*>::iterator iter = this->__nfa.begin();


		for (iter; iter != this->__nfa.end(); iter++)
		{

			NFAGraph *nfaTemp = (*iter);
			NFAGraph::merge((State*)nfaTemp->getInitial(), NULL, link);

		}

		result->setInitial(link);
		dfa = result->toDFA();
	}
	else
	{
		dfa->loadXMLGraph(L"lspec.xml");
		//load the DFAgraph from disk
	}
	
	
	return dfa;
}


void GrammarLexeme::useDefault()
{
	if (IsLoadFromDisk)
	{
     //load from disk here
		this->loadXMLLexicalNodes();
	}
	else{
		this->initalised();
	}
}
void GrammarLexeme::loadXMLLexicalNodes()
{

}
