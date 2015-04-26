#include "stdafx.h"
#include "transition.h"
#include "state.h"
using namespace obaro::graphs;

State* Transition::getState()
{
	return (State*)this->getNode();
}