#include "stdafx.h"
#include "State.h"

using namespace obaro::graphs;

State::State(int32_t n) :Node(n)
{

}

State::State(std::set<State*>& states, int32_t n) :
Node(n)
{
	this->states_nfa = states;
	this->n = n;
	this->state = StateType::NONE_STATE;
	this->tokenID = TokenClass::INVALID_TOKEN;
	this->markFinalState();
}
void State::markFinalState()
{
	if (this->states_nfa.size() > 0)
	{
		std::set<State*>::iterator iter = this->states_nfa.begin();
		for (iter; iter != this->states_nfa.end(); iter++)
		{
			State* next = *iter;
			if (next == NULL)continue;

			if (next->state==StateType::FINAL_STATE)
			{
				//if final mark this state final state
				this->state = next->state;
				this->tokenID = next->tokenID;
				//std::cout << "\nFinal State : " << this->label << "\n";
			}
		}
	}
}

void State::addEdge(Edge *edge)
{
	if (edge == NULL)
		return;
	//Add the a new Edge to the Node edges
	this->edges.push_back(edge);
}

