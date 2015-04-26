#include "stdafx.h"
#include"Node.h"
#include "Edge.h"
#include <iostream>

using namespace obaro::graphs;

Node::Node(INT32 n)
{
	this->n = n;
}

bool Node::hasEdge(Edge *edge)
{
	//std::vector<Edge*>::iterator iter = this->edges.begin();
	for each (Edge* _edge in this->edges)
	{
		if (_edge->getLabel() == edge->getLabel())
		{
			return true;
		}
	}
	return false;
}

void Node::addEdge(Edge *edge)
{
	if (!this->hasEdge(edge))
	{
		this->edges.push_back(edge);
	}

}

void Node::removeEdge(Edge *edge)
{
	if (this->hasEdge(edge))
	{
		delete edge;
	}
}
std::vector<Edge*> Node::Edges()
{
	return this->edges;
}