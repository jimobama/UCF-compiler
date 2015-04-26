#ifndef XML_PUSH_READER_H
#define XML_PUSH_READER_H
#include <stdint.h>
#include <shlwapi.h> 
#include <ole2.h> 
#include <xmllite.h> 
#include <atlbase.h>
#include<string>
#include <IGraph.h>

using namespace obaro::graphs;
namespace obaro
{

	namespace xml
	{
		class XMLAttribute;
		class XMLElement;
		class XMLTextElement;


		class XMLReader:public IGraph
		{
		private:
			IXmlReader * pReader;
			XMLElement *root;
			std::wstring filename;
			void parserRootElement(uint32_t depth);
			void initialisedReader();
			void parserChildElements(XMLElement * parent, uint32_t level=0);
			void XMLReader::initialStandardElements();
		public:
			XMLReader(std::wstring filename);
			XMLElement * getRootElement();


		};
	}
}

#endif