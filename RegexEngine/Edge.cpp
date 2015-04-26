#include"stdafx.h"
#include"Edge.h"
#include "Node.h"

using namespace obaro::graphs;


Edge::Edge()
{

}
Node * Edge::getEndPoint()
{
	return this->endPoint;
}
void Edge::setEndPoint(Node* node)
{
	this->endPoint = node;

}
void Edge::setLabel(char c)
{
	this->ch = c;
}
Node * Edge::getNode()
{
	return this->endPoint;
}
char  Edge::getLabel()
{
	return ch;
}