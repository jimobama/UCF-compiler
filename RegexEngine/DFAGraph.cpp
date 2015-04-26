// DFAGraph.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "DFAGraph.h"
#include "State.h"
#include "Transition.h"
#include <fstream>
#include<string>


using namespace obaro::graphs;
int32_t DFAGraph::xmlFomatter = 0;

std::set<State*> *DFAGraph::__staticVisitedNodes = new std::set<State*>();

DFAGraph::DFAGraph() :IGraph()
{
	this->initial = NULL;
}
DFAGraph::DFAGraph(State *root)
{
	this->initial = root;
}

void DFAGraph::addNode(Node* node)
{
	if (node == NULL)
		return;

	if (!this->hasNode(node))
	{
		//std::cout << node->getN();
		this->states.push_back(node);
	}
}


void DFAGraph::setRootNode(State* state)
{
	//ignore null state
	if (state == NULL) return;
	//check if its already have the node else add the node
	if (!this->hasNode(state))
	{
		this->addNode(state);
	}
	this->initial = state;
}

//Check if the state exists
bool DFAGraph::hasNode(Node* state)
{
	for each(Node *s in this->states)
	{
		if (s == state)
		{
			return true;
		}
	}

	return false;
}

State * DFAGraph::delta(State* state, char ch)
{
	
	if (state == NULL)
		return NULL;

	std::vector<Edge*> edges = state->Edges();
	for each(Edge *edge in edges)
	{
		if (edge->getLabel() == ch)
		{
			return (State*) edge->getNode();
		}
	}
	return NULL;
}

void DFAGraph::reduce()
{
	for each(Node* state in this->states)
	{
		std::vector<Edge*> edges = state->Edges();
		for each(Edge *edge in edges)
		{
			if (this->isDeadEnd((State*)edge->getEndPoint()))
			{
				//remove the edge from the state links
				state->removeEdge(edge);
			}
		}
	}
}

bool DFAGraph::isDeadEnd(State *node)
{
	if (node == NULL) return false;
	if (node->state != StateType::FINAL_STATE)
	{
		if (node->Edges().size() <= 0)
			return true;
	}
	return false;
}

void DFAGraph::saveTo(DFAGraph* dfa, std::wstring filename)
{

	HRESULT hr = S_OK;
	IStream *pOutFileStream = NULL;
	IXmlWriter *pWriter = NULL;
	DFAGraph::xmlFomatter = 0;


	//Open writeable output stream 
	if (FAILED(hr = SHCreateStreamOnFile(filename.c_str(), STGM_CREATE | STGM_WRITE, &pOutFileStream)))
	{
		wprintf(L"Error creating file writer, error is %08.8lx", hr);
		return;
	}

	if (FAILED(hr = CreateXmlWriter(__uuidof(IXmlWriter), (void**)&pWriter, NULL)))
	{
		wprintf(L"Error creating xml writer, error is %08.8lx", hr);
		return;
	}

	if (FAILED(hr = pWriter->SetOutput(pOutFileStream)))
	{
		wprintf(L"Error, Method: SetOutput, error is %08.8lx", hr);
		return;
	}
	if (FAILED(hr = pWriter->SetProperty(XmlWriterProperty_Indent, TRUE)))
	{
		wprintf(L"Error, Method: SetProperty XmlWriterProperty_Indent, error is %08.8lx", hr);
		return;
	}

	pWriter->WriteStartDocument(XmlStandalone_Yes);
	pWriter->SetProperty(XmlWriterProperty_Indent, TRUE);
	pWriter->WriteComment(L"The document is XML specification of the UCF programming language ");
	pWriter->WriteComment(L"The Finite State Machine Graph In XML ");


	//create the Main Node of the graph
	pWriter->WriteStartElement(L"ucf", L"graph", L"https:://github.org/jimobama/speci");
	std::wstring nsize = std::to_wstring(dfa->size());
	pWriter->WriteAttributeString(NULL, L"size", NULL, nsize.c_str());
	//create a start node and 
	DFAGraph::__staticVisitedNodes->clear();
	pWriter->WriteWhitespace(L"\n\n");
	writeNode(pWriter,(State*) dfa->getInitial());

	pWriter->WriteWhitespace(L"\n");
	pWriter->WriteEndElement();
	pWriter->WriteEndDocument();


	//Now we can continue;

	pWriter->Flush();


}

void DFAGraph::writeNode(IXmlWriter *&writer,State *node)
{
	int32_t  spaces = DFAGraph::xmlFomatter++;	
	DFAGraph::formatWritter(writer, spaces);

	if (!DFAGraph::IsVisit(node))	 {
		DFAGraph::MarkVisit(node);
		DFAGraph::xmlFomatter++;
		writer->WriteWhitespace(L"\n");
		DFAGraph::formatWritter(writer);

		writer->WriteStartElement(L"ucf", L"state", NULL);
		//state attributes
		std::wstring nlabel = std::to_wstring(node->getN());
		writer->WriteAttributeString(NULL, L"id", NULL, nlabel.c_str());
		std::wstring ntype = std::to_wstring(node->state);
		writer->WriteAttributeString(NULL, L"stateType", NULL, ntype.c_str());
		std::wstring ntypeToken = std::to_wstring(node->tokenID);
		writer->WriteAttributeString(NULL, L"tokenType", NULL, ntypeToken.c_str());
		writer->WriteAttributeString(NULL, L"nEdges", NULL, std::to_wstring(node->Edges().size()).c_str());



		std::vector<Edge*> edges_t = node->Edges();
		std::vector<Edge*>::iterator iter = edges_t.begin();
		//process each edges 
		for (iter; iter != edges_t.end(); iter++)
		{
			
			wchar_t c = (*iter)->getLabel();
			writer->WriteStartElement(L"ucf", L"transition", NULL);
			std::wstring schar = L"";
			schar.push_back(c);
			//write transition attributes
			writer->WriteAttributeString(NULL, L"weight", NULL, schar.c_str());
			std::wstring sId = std::to_wstring((*iter)->getEndPoint()->getN());
			writer->WriteAttributeString(NULL, L"endPoint", NULL, sId.c_str());
			//

			State *nextNode =(State*) (*iter)->getNode();
			writeNode(writer, nextNode);
			writer->WriteWhitespace(L"\n");
			DFAGraph::formatWritter(writer, spaces);
			writer->WriteEndElement();//end edges
		}

		writer->WriteWhitespace(L"\n");
		DFAGraph::xmlFomatter = 1;
		DFAGraph::formatWritter(writer, spaces);
		writer->WriteEndElement();


	}
}

bool  DFAGraph::IsVisit(State *node)
{
	if (node == NULL)
	{
		return true;
	}

	std::set<State*>::iterator iter = DFAGraph::__staticVisitedNodes->begin();
	for (iter; iter != DFAGraph::__staticVisitedNodes->end(); iter++)
	{
		if ((*iter) == node)
		{
			return true;
		}
	}
	return false;
}
void  DFAGraph::MarkVisit(State *node)
{
	if (node == NULL)
		return;

	DFAGraph::__staticVisitedNodes->insert(node);
}

void DFAGraph::formatWritter(IXmlWriter *&writer, int32_t counter)
{


	for (int32_t i = 0; i <= counter; i++)
	{
		writer->WriteWhitespace(L"\t");
	}

}


//Read the element from the xml files and graph a graph object


DFAGraph*   DFAGraph::loadXMLGraph(std::wstring filename)
{
	HRESULT hr = S_OK;
	IStream *pFileStream;
	IXmlReader *pReader;
	//Open read-only input stream 
	if (FAILED(hr = SHCreateStreamOnFile(filename.c_str(), STGM_READ, &pFileStream)))
	{
		wprintf(L"Error creating file reader, error is %08.8lx", hr);
		return NULL;
	}
	if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**)&pReader, NULL)))
	{
		wprintf(L"Error creating xml reader, error is %08.8lx", hr);
		return NULL;
	}

	if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
	{
		wprintf(L"Error setting XmlReaderProperty_DtdProcessing, error is %08.8lx", hr);
		return NULL;
	}

	if (FAILED(hr = pReader->SetInput(pFileStream)))
	{
		wprintf(L"Error setting input for reader, error is %08.8lx", hr);
		return NULL;
	}
	pReader->SetProperty(XmlReaderProperty_MaxElementDepth, 12000);
	return parserXmlGraphFile(pReader);


}


DFAGraph * DFAGraph::parserXmlGraphFile(IXmlReader *&reader)
{

	DFAGraph *graph = NULL;
	//the reader is here
	if (reader != NULL)
	{
		XmlNodeType nodeType;
		if (reader->Read(&nodeType) == S_OK)
		{

			switch (nodeType)
			{

			case XmlNodeType_Element:
			{
				uint32_t nDepth;
				reader->GetDepth(&nDepth);
				parserElement(reader, nDepth);
				break;
			}
			default:
			{
				parserXmlGraphFile(reader);
				break;
			}

			}



		}

	}
	return graph;

}


void DFAGraph::parserElement(IXmlReader *&reader, uint32_t uCounter)
{


	LPCWSTR name, value;
	reader->GetLocalName(&name, NULL);
	reader->GetValue(&value, NULL);
	HRESULT hr = reader->MoveToFirstAttribute();
	while (hr == S_OK)
	{
		reader->GetLocalName(&name, NULL);
		reader->GetValue(&value, NULL);		
		hr = reader->MoveToNextAttribute();
	}

	DFAGraph * dfa = new DFAGraph();
	skipNonElementType(reader);
	
	//Create the first Node
	State * node = NULL;
	uint32_t nCounter;
	reader->GetDepth(&nCounter);
	node = parserNode(reader);
	if (node != NULL){		
		dfa->setRootNode(node);
		skipNonElementType(reader);
		parserEdges(reader,dfa, node, nCounter);

	}




}

void  DFAGraph::parserEdges(IXmlReader *&reader, DFAGraph *&dfa, State*& parent, int32_t nCounter)
{


}

bool DFAGraph::isStateIDExist(int32_t id)
{
	std::vector<Node*>::iterator iter = this->states.begin();
	bool isOkay = false;
	for (iter; iter != this->states.end(); iter++)
	{
		int32_t index = (*iter)->getN();
		if (index == id)
		{
			isOkay = true;
			break;
		}
	}
	return isOkay;
}
State* DFAGraph::getStateByID(int32_t id)
{

	std::vector<Node*>::iterator iter = this->states.begin();
	State *temState = NULL;
	for (iter; iter != this->states.end(); iter++)
	{
		int32_t index = (*iter)->getN();
		if (index == id)
		{
			temState =(State*) (*iter);
			break;
		}
	}

	return temState;
}

State*  DFAGraph::parserNode(IXmlReader *&reader)
{
	LPCWSTR name, value;
	State *node= NULL;

	if (reader->IsEOF())
		return node;
	//we are looking for nodes if the element is node a node type report error]
	reader->GetLocalName(&name, NULL);
	if (std::wcscmp(name, L"state") != 0)
	{
		std::wcerr << "Node element expected but " << name << " found in xml lexical specification file\n";
		return node;
	}

	if (reader->MoveToAttributeByName(L"id", NULL) == S_OK)
	{
		reader->GetValue(&value, NULL);
		std::wstring wstrValue = value;
		uint32_t id = std::stoi((wstrValue.c_str()));
		node = new State(id);
	}
	if (reader->MoveToAttributeByName(L"tokenType", NULL) == S_OK && node != NULL)
	{
		reader->GetValue(&value, NULL);
		std::wstring wstrValue = value;
		uint32_t typeToken = std::stoi((wstrValue.c_str()));
		node->tokenID =(TokenClass)typeToken;
	}

	if (reader->MoveToAttributeByName(L"stateType", NULL) == S_OK && node != NULL)
	{
		reader->GetValue(&value, NULL);
		std::wstring wstrValue = value;
		uint32_t type = std::stoi((wstrValue.c_str()));

		switch (type)
		{
		case 2:
		{
			node->state = StateType::FINAL_STATE;
			break;
		}
		case 1:
			node->state = StateType::INITIAL_STATE;
			break;
		default:
			node->state = StateType::NONE_STATE;
			break;
		}
	}

	
	return node;

}
void DFAGraph::skipNonElementType(IXmlReader *&reader)
{
	if (reader->IsEOF())
	{
		return;
	}


	XmlNodeType nodeType;
	reader->Read(&nodeType);
	//skip all type of node ecapse element nodes
	while (nodeType != XmlNodeType_Element || nodeType==XmlNodeType_EndElement)
	{
		reader->Read(&nodeType);
	}
}


void DFAGraph::setAlphabet(std::set<char> inputs)
{
	this->alphabets= inputs;
}
DFAGraph::~DFAGraph()
{
	delete this->initial;
	//delete this->alphabets;

}