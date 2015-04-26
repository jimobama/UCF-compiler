#include "stdafx.h"
#include <Windows.h>
#include "IGraph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <stdint.h>



using namespace obaro::graphs;


IGraph::IGraph()
{
	this->initial = NULL;
	counter = 0;
}
void IGraph::print()
{
	printNode(this->getInitial());
}
void IGraph::printNode(Node *node)
{
	
	if (!isVisit(node))
	{
		markVisit(node);		
		//std::cout << "Node = " << node->getN() << " with edges= " << node->Edges().size() << "\n";
		std::vector<Edge*> edges_t = node->Edges();
		std::vector<Edge*>::iterator iter = edges_t.begin();

		for (iter; iter != edges_t.end(); iter++)
		{
			node = (*iter)->getNode();
			char c = (*iter)->getLabel();	
			if (c != EPSILON__)
			this->addCharacter(c);
			printNode(node);

		}

	}
}

bool IGraph::isVisit(Node *node)
{

	if (node == NULL)
	{
		return true;
	}

	std::set<Node*>::iterator iter = IGraph::visitedNodes.begin();
	for (iter; iter !=IGraph::visitedNodes.end(); iter++)
	{
		if ((*iter) == node)
		{
			return true;
		}
	}
	return false;
}


void IGraph::markVisit(Node *node)
{
	if (node == NULL)
		return;
	this->addNode(node);
	visitedNodes.insert(node);
}




std::vector <Node*>* IGraph::getNodes()
{
	std::vector <Node*>* nodes = new std::vector <Node*>();
	*nodes = states;

	return nodes;
}

int32_t IGraph::size()
{
	return this->states.size();
}

void IGraph::connect(Node* s1, Node* s2, const char c)
{
	if (s1 == NULL)
	{
		return;
	}
	Edge *edge = new Edge();
	edge->setLabel(c);
	//std::cout << s1->getN() << " to (" << ((c =='\0') ? ' ' : c) << ")" << s2->getN() << std::endl;
	edge->setEndPoint(s2);
	s1->addEdge(edge);
	//Add the states to the nodes
	this->addNode(s1);
	this->addNode(s2);
}


void	IGraph::setInitial(Node* initial)
{
	this->initial = initial;
	if (this->initial != NULL)
	{
		this->addNode(this->initial);
	}
}
Node*	IGraph::getInitial()
{
	return this->initial;
}
void IGraph::addAllCharacters()
{
    
}
std::set<char>  IGraph::getCharacterSets()
{
	return this->alphabets;
}
 void IGraph::addCharacter(char c)
{
	if (c == EPSILON__) return;
	this->alphabets.insert(c);

	
}



 


 

