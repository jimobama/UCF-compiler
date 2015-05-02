#include "stdafx.h"

#include "NFAGraph.h"
#include  "State.h"
#include "Edge.h"
#include "Transition.h"
#include "stateType.h"
#include "DFAGraph.h"
#include "lexicalanalyserexception.h"
#include <InfixExpression.h>
#include<algorithm>



using  namespace obaro::core;
using namespace obaro::graphs;



//Constructor
NFAGraph::NFAGraph()
{
	this->next_state_counter = 0;
	this->token_id = TokenClass::INVALID_TOKEN;	
	this->lang = NULL;
}
//Parameterised constructor
NFAGraph::NFAGraph(obaro::core::Language *language, TokenClass atoken_id):
lang(language)
{
	
	if (lang != NULL)
	{
		this->next_state_counter = 0;		
		this->token_id = atoken_id;
		
	}
	else
		//else
throw new LexicalAnalyserException("non-deterministic finite machine require a valid regular language to be able to run.");
}



bool NFAGraph::is_input_unique(char c, std::set<char> &inputs)
{


	std::set<char>::iterator iter = inputs.find(c);
	if (iter != inputs.end())
	{
		return false;
	}

	return true;
}


//Tested and working fine Sub-contruction for NFA to DFA
DFAGraph *NFAGraph::toDFA()
{
	DFAGraph *dfaGraph = new DFAGraph();

	if (this->initial == NULL || this->initial->Edges().size() < 0)
		return dfaGraph;	
	this->print();

	std::cout << "Please wait.....\n";
	//reset the pointer to new create DFA states
	this->next_state_counter = 0;

	std::vector<State*> unprocessed_dfa_states;


	std::set<State*> start_state_dfa = this->e_closure((State*)this->initial);
	
	//create a new state for the DFA
	State* new_DFAState =new State(start_state_dfa, ++(this->next_state_counter));

	new_DFAState->state = StateType::INITIAL_STATE;
	
	//set the start state
	dfaGraph->setInitial(new_DFAState);
	//add it to the DFA states;
	dfaGraph->addNode(new_DFAState);
	dfaGraph->setAlphabet(this->alphabets);


	//add the starting states to the set of unprocess dfa sets unmark it
	unprocessed_dfa_states.push_back(new_DFAState);
	
 
	while (!unprocessed_dfa_states.empty())
	{
		State* unmark_DFAState = unprocessed_dfa_states[unprocessed_dfa_states.size() - 1];
		unprocessed_dfa_states.pop_back();
		
		
	
		
		//For each input simulate the NFA to DFA
		std::set<char>::iterator iter = this->alphabets.begin();
		
		
		for (iter; iter != this->alphabets.end(); ++iter)
		{
			//create e_closure states and move states
			std::set<State*> closure_states, move_states;			
			move_states = this->move(unmark_DFAState->states_nfa, (*iter));

			//Check if there is a transition from that input symbol
			if (move_states.size() == 0)
				continue;//else got to the next loop section
			
			//take the closure of the move states
			closure_states = this->e_closure(move_states);

			//Check if the closure_states already exist in the DFA states 

			bool aFound = false;
			std::set<State*> *DFATAble = this->set_to_vector((std::vector<State*>*) dfaGraph->getNodes());

			//std::cout << DFATAble->size() << std::endl;
			std::set<State*>::iterator iter_DFATable = DFATAble->begin();
			State * DFA_State_Temp = NULL;
			for (iter_DFATable; iter_DFATable != DFATAble->end(); iter_DFATable++)
			{
				DFA_State_Temp = *iter_DFATable;

				if (DFA_State_Temp->states_nfa == closure_states)
				{
					aFound = true;
					break;
				}
			}
			//check if found
			if (!aFound)
			{
				//create new DFA state with the closure
				State * dfaState = new State(closure_states, ++(this->next_state_counter));
				unprocessed_dfa_states.push_back(dfaState);
				//add a transition from the previous (unmark_DFAState)state to the new dfaStates
				dfaGraph->connect(unmark_DFAState, dfaState, (*iter));			
				

			}
			else
			{
				//The states already exists so add a transition from the preocess state 
				//to the last state that look reaches
				dfaGraph->connect(unmark_DFAState, DFA_State_Temp, *iter);
				
			
			}

		}


	}
	//Clear and delete NFA states from memory
//	this->final_state();
	//std::cout << DFA.GetStateTable().size()<<" DFA States successfully created\n";
	//std::cout << DFA->size();
	return dfaGraph;

}

//compiles the regex to NFA
void NFAGraph::compile()
{
	
	SStream *regex = this->lang->toStream();
	
	this->create_NFAutomata(*regex);
	this->final_state();

}

std::set<State*>*  NFAGraph::set_to_vector(std::vector<State*>* vectors)
{
	std::set<State*> *__states = new std::set<State*>();

	if (vectors == NULL || vectors->size() == 0)
		return __states;

	std::vector<State*>::iterator iter_state = vectors->begin();

	for (iter_state; iter_state != vectors->end(); iter_state++)
	{
		//insert each of the a set
		__states->insert(*iter_state);
	}

	return __states;

}
/*comment
The method will generate an non-deterministic finite automata base on the postfix regular expression provided
*/

void NFAGraph::create_NFAutomata(SStream regex)
{
	while (regex.hasNext())
	{
		Symbol *current = (Symbol*)regex.current();
		
		switch (current->type)
		{
			
		case obaro::core::symbol_type::OPERATOR:
		{
			
			switch (current->getValue())
			{
			case REGEX_CONST::CONCATENATION:

				this->concat();
				break;
			case REGEX_CONST::KLEENE_STAR:
				
				this->kleene_star();
				break;
			case REGEX_CONST::UNION:
				this->union_op();				
				break;
			case REGEX_CONST::PLUS:
			
				this->plus_op();
				break;
			default:
				break;
			}
		}break;
		case obaro::core::symbol_type::LITERAL:
		default:
			
			this->push_new_state(current->getValue());
			break;
		}
		regex.advance();
	}
}


/*Comments
A helper method to convert a set to stack

*/
std::stack<State*> NFAGraph::set_to_stack(std::set<State*> sets)
{
	std::stack<State*> stacks;

	std::set<State*>::iterator iter = sets.begin();
	while (iter != sets.end())
	{
		stacks.push(*iter);
		iter++;
	}
	return stacks;
}



/*Comment
return a;; the NFA_States that can be research with epsilon transition from the current state
/*/
std::set<State*> NFAGraph::e_closure(State *initial)
{
	std::set<State*> sets;
	if (initial == NULL)
		return sets;
	sets.insert(initial);
	
	sets = this->e_closure(sets);
	
	return sets;
}



/*
The e_closure algorithm implementation of NFAutomata
*/
std::set<State*> NFAGraph::e_closure(std::set<State*> sets)
{
	// convert the set container to stack
	std::stack<State*> stacks = this->set_to_stack(sets);
	//set the results to the same sets, since e-closure of a state also contain the state itself
	std::set<State*> results = sets;

	// loop the stack not
	while (!stacks.empty())
	{
		//pop the state from a stack
		State *st = stacks.top();
		stacks.pop();
		if (st != NULL){

			// check if the current NFA_States transition have epsilon transitions from its paths
			std::vector<Edge*> arrows = st->Edges();
			std::vector<Edge*>::iterator iter = arrows.begin();

			//for each transition arrow from state check if the weight is epsilon
			for (iter; iter != arrows.end(); iter++)
			{

				if ((*iter)->getLabel()== Transition::EPSILON)
				{
					State * tem_state =(State*) (*iter)->getEndPoint();

					// check if the state as already be added into the stack
					if (!this->is_exits_in(sets, tem_state))
					{
						//add the state to the results
						results.insert(tem_state);
						//push to the NFA_States stack
						stacks.push(tem_state);
					}
				}

			}//the for statements

		}//the while statements
	}
	//std::cout << "Yes o\n";
	return results;
}



//checj if the given state exist in the set of states provided
bool const NFAGraph::is_exits_in(std::set<State*> sets, State* s)
{

	std::set<State*>::iterator iter = sets.find(s);
	if (iter != sets.end())
		return true;
	return false;

}


/*Comments
The method pop out element from the stack, if there is not fragment it create epsilon frament  then return it
*/
std::pair<State*, State*> NFAGraph::pop()
{
	std::pair<State*, State*> frag;
	//if there is no state to
	if (this->OP_NFAState.empty())
	{
		State* s1 = new State(++this->next_state_counter);
		State* s2 = new State(++this->next_state_counter);

		frag.first = s1;
		frag.second = s2;
		//connect them and push to stack
		this->connect(s1, s2, Transition::EPSILON);
		this->OP_NFAState.push(frag);
	}

	frag = this->OP_NFAState.top();
	this->OP_NFAState.pop();
	//return the NFA_States
	return frag;

}


/*Comments
The method will return the all the NFA_States that can be reach from individual state in the sets of NFA_States with transition character c
*/

std::set<State*> NFAGraph::move(std::set<State*> sets, const char c)
{

	std::set<State*>::iterator iter = sets.begin();
	std::set<State*> result;

	for (iter; iter != sets.end(); iter++)
	{
		if (*iter == NULL)continue;
		//get the that transition arrows
		std::vector<Edge*> arrows = (*iter)->Edges();
	
		std::vector<Edge*>::iterator iter_t = arrows.begin();

		for (iter_t; iter_t != arrows.end(); iter_t++)
		{
			Transition * transition = (Transition*)(*iter_t);
			//check if there is a state transition with the character c 
			if (transition->getLabel() == c)
			{
				//Add it to the result state
				result.insert((State*)transition->getEndPoint());
			}

		}
	}

	//result the set of the NFA_States reach with transition character label c
	return result;
}


//Push new node into the operator stack
void NFAGraph::push_new_state(char const c)
{
	// create a single character literal
	State* s1 = new State(++next_state_counter);
	State* s2 = new State(++next_state_counter);
	//transit the character c to the next state;
	this->connect(s1, s2, c);

	// push in the create NFA_States framgents
	std::pair<State*, State*> fragent;
	fragent.first = s1;
	fragent.second = s2;
	//push the frament into the stack
	this->OP_NFAState.push(fragent);
	
	//save the character
	this->alphabets.insert(c);
}


/*The Kleene star algorithm implementation */
void NFAGraph::kleene_star()
{
	///create addition two state
	State* initNode = new State(++this->next_state_counter);
	State* finalNode = new State(++this->next_state_counter);
	//Connect the initNode to the FinalNode with Epison transition
	this->connect(initNode, finalNode, Transition::EPSILON);
	
	//Following thompson algorithm ; pop out the first fragement from the stack
	std::pair<State*, State*> f1 = this->pop();

	//Connect the initNode to first of f1 with epison label

	this->connect(initNode,f1.first, Transition::EPSILON);
	//connect the second of the f1 to the finalNode
	this->connect(f1.second, finalNode, Transition::EPSILON);

	//finally connect the second of f1 to the first of f1
	this->connect(f1.second, f1.first, Transition::EPSILON);
	
	//Create a new fragement pair and push into stack
	std::pair<State*, State*> pair;
	pair.first = initNode;
	pair.second = finalNode;
	//push to the stack
	this->OP_NFAState.push(pair);

}



/*comments

*/
void NFAGraph::concat()
{
	//Create two fragment 
	std::pair<State*, State*> f1, f2;
	//pop out tow fragement from the stack and eval the concatenation rule
	f2 = this->pop();
	f1 = this->pop();
	
	
   //connect the second of f1 to the first of f2 with epison position
	this->connect(f1.second, f2.first,Transition::EPSILON);
	//create another pair for first of f1 and second of f2

	std::pair<State*, State*> pair;
	pair.first = f1.first;
	pair.second = f2.second;
	//push into the stack
	this->OP_NFAState.push(pair);
	

}



/*comment
*/
void NFAGraph::union_op()
{
	//create two more addition NFA_States
	State* e_init = new State(++this->next_state_counter);
	State* e_final = new State(++this->next_state_counter);

	//Following the union rule pop out two frament from the stack

	std::pair<State*, State*> f2 = this->pop();
	std::pair<State*, State*> f1 = this->pop();


	//Connect e_init to first of both f1 and f2 with Epison transition
	this->connect(e_init, f1.first, Transition::EPSILON);
	this->connect(e_init, f2.first, Transition::EPSILON);

	//connect the f1 and f2 second node to the e_final node
	this->connect(f1.second, e_final, Transition::EPSILON);
	this->connect(f2.second, e_final, Transition::EPSILON);
	

	//my new fragment will be the e_state and the final_state;
	std::pair<State*, State*> pairs;
	pairs.first = e_init;
	pairs.second = e_final;
	//push it into the stack
	this->OP_NFAState.push(pairs);
}


//Plus operators
void NFAGraph::plus_op()
{
	///create addition two state
	State* e_init = new State(++this->next_state_counter);
	State* e_final = new State(++this->next_state_counter);

	//following thompson algorithm pop only one item from the state
	std::pair<State*, State*> f1 = this->pop();

	//connect an epsilon transition from init to f1.first
	this->connect(e_init, f1.first, Transition::EPSILON);	

	//connect an epsilon transition from f1.second to final
	this->connect(f1.second, e_final, Transition::EPSILON);
	
	//connecta loop  epsilon transition from f1.second to f1.first
	this->connect(f1.second, f1.first, Transition::EPSILON);

	//We are interest on the e_init and e_final  then add them to the transition table stack
	std::pair<State*, State*> pair;
	pair.first = e_init;
	pair.second = e_final;

	//push to the stack
	this->OP_NFAState.push(pair);
}

//set the final state
void NFAGraph::final_state()
{
	if (!this->OP_NFAState.empty())
	{
		std::pair<State*, State*> pair = this->OP_NFAState.top();
		pair.second->tokenID = this->token_id;
		pair.second->state = StateType::FINAL_STATE;
		pair.first->state = StateType::INITIAL_STATE;
		this->initial= pair.first;
		this->OP_NFAState.pop();
		
	}

	/*throw exception if there is items in the stack
	if (!this->OP_NFAState->empty())
	throw obaro::core::lexical_analysis_exception("error: regular expression is invalid could not finish connecting all the NFA_States.");
	/ throw exceptions state creations was not successfully*/
}




//Implementation  of the inherited member functions


void NFAGraph::addNode(Node* state)
{
	if(!this->hasNode(state))
	{
      //Add 		
		this->states.push_back(state);
	}
	
}

bool NFAGraph::hasNode(Node* state)
{
	bool isOkay = false;

	if (std::find(this->states.begin(), this->states.end(), state) != states.end())
	{
		isOkay = true;
	}

	return isOkay;
}


/*
void  NFAGraph::connect(Node* s1, Node* s2, const char c)
{
	if (s1 == NULL )
	{
		return;
	}
	Edge *edge = new Edge();
	edge->setLabel(c);
	std::cout <<s1->getN() <<" to (" <<( (c == Transition::EPSILON) ? '%': c)<< ")" << s2->getN() << std::endl;
	edge->setEndPoint(s2);
	s1->addEdge(edge);
	//Add the states to the nodes
	this->addNode(s1);
	this->addNode(s2);
}
*/

void  NFAGraph::merge(State *node1, State *node2, State*& linkNode, const char c)
{
	if (linkNode != NULL)
	{
		
		if (node1 != NULL){
			Edge *edge = new Edge();
			edge->setLabel(c);
			edge->setEndPoint(node1);
			linkNode->addEdge(edge);
			//std::cout << "\nNumber is: " << linkNode->Edges().size();
		}
		//std::cout << "\nNumber is: " << node->Edges().size();
		if (node2 != NULL){
			
			Edge *edge1 = new Edge();
			edge1->setLabel(c);
			edge1->setEndPoint(node2);
			linkNode->addEdge(edge1);
			
		}
		
	}
 

}


NFAGraph::~NFAGraph()
{

}
