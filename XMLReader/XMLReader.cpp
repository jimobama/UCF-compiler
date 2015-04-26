// XMLReader.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "XMLReader.h"
#include "XMLElement.h"

using namespace obaro::xml;


XMLReader::XMLReader(std::wstring filename)
{
	this->root = NULL;
	this->filename=filename;
	this->initialisedReader();
}

void XMLReader::initialisedReader()
{
	HRESULT hr = S_OK;
	IStream *pFileStream;
	
	//Open read-only input stream 
	if (FAILED(hr = SHCreateStreamOnFile(filename.c_str(), STGM_READ, &pFileStream)))
	{
		wprintf(L"Error creating file reader, error is %08.8lx", hr);
		return;
	}
	if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**)&pReader, NULL)))
	{
		wprintf(L"Error creating xml reader, error is %08.8lx", hr);
		return;
	}

	if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
	{
		wprintf(L"Error setting XmlReaderProperty_DtdProcessing, error is %08.8lx", hr);
		return ;
	}

	if (FAILED(hr = pReader->SetInput(pFileStream)))
	{
		wprintf(L"Error setting input for reader, error is %08.8lx", hr);
		return;
	}
	//set read depth to 500
	pReader->SetProperty(XmlReaderProperty_MaxElementDepth, 500);

	this->initialStandardElements();
}

void XMLReader::initialStandardElements()
{
	if (this->pReader != NULL && !this->pReader->IsEOF())
	{
		XmlNodeType nodeType;
		if (pReader->Read(&nodeType))
		{
			switch (nodeType)
			{
              // we only need to get a root element
				case XmlNodeType_Element:
				{
					//if the depth is 0 ; means its the root element
					uint32_t nDepth;
					this->pReader->GetDepth(&nDepth);
					if (nDepth == 0)
					{
						this->parserRootElement(nDepth);
						this->parserChildElements(this->root,nDepth);
						break;
					}
					
				   break;
				}
				default:{
					this->initialStandardElements();
					break;
				}
			}
		}
	}
}



void XMLReader::parserChildElements(XMLElement * parent,uint32_t level)
{
	if (parent == NULL)
		return;





}
void XMLReader::parserRootElement(uint32_t depth)
{
	LPCWSTR  pwszLocalName, aValue, aName,nameSpace;
	uint32_t  uCounter;

	this->pReader->GetLocalName(&pwszLocalName, NULL);
	this->pReader->GetPrefix(&nameSpace, NULL);
	this->pReader->GetValue(&aValue, NULL);
	
   //Set Element
	root = new  XMLElement(pwszLocalName);
	root->setPrefix(nameSpace);
	root->setZIndex(depth);

	if (aValue != L"")
	{
		root->setText(aValue);
	}

	//move to the first attribute of the element and parser it 
	HRESULT hr= this->pReader->MoveToFirstAttribute();
	while (hr == S_OK)
	{
	    this->pReader->GetPrefix(&nameSpace, NULL);
		this->pReader->GetLocalName(&pwszLocalName, NULL);
		this->pReader->GetValue(&aValue, NULL);
		//set the attribute values
		XMLAttribute *attribute = new  XMLAttribute(pwszLocalName);
		attribute->setValue(aValue);
		attribute->setPrefix(nameSpace);
		this->root->addAttribute(attribute);

		hr = this->pReader->MoveToFirstAttribute();
	}

}
XMLElement * XMLReader::getRootElement()
{
	return this->root;
}