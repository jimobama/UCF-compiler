#ifndef XML_ELEMENT_H
#define  XML_ELEMENT_H
#include <string>
#include <Node.h>
using namespace obaro::graphs;
namespace obaro
{
	namespace xml
	{
		class XMLAttribute;
		class  XMLElement:public Node
		{
		public:
			XMLElement(std::wstring elementname);
			void setPrefix(std::wstring prefix);
			void setZIndex(uint32_t index);
			void setText(std::wstring  text);

			void addAttribute(XMLAttribute *attr);
		};
	}
}
#endif
