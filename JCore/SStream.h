#ifndef JSYMBOL_STREAM_H
#define JSYMBOL_STREAM_H

/*Explanations


*/
#ifdef JCORE_EXPORTS
#define  SYMBOL_STREAM_API __declspec(dllexport) 
#else
#define SYMBOL_STREAM_API  //__declspec(dllimport) 
#endif

#include "stdafx.h"
#include <vector>
#include "Comparable.h"
#include <iostream>
#include <memory>
#include "Symbol.h"

//#pragma warning (disable : C4251)
namespace obaro{
	namespace core{

	
		class  SYMBOL_STREAM_API  SStream : public Comparable <SStream & >
		{
		private:
			
			std::vector<  Symbol*>   symbols;
			int32_t index_position;
		public:


			//The parameters symbolstreams constructors
			   SStream();
			   SStream(std::string characters);
			   SStream(const char* characters);
			  ~SStream();
			  int32_t const			size();
			   bool				compareTo(SStream& classDerive);
			  const Symbol*		current();
			  void				advance(int32_t n = 1);
			  void				seekp(int32_t n);
			  Symbol*			peek(int32_t n = 1);
			  	bool				hasNext();
				Symbol*				behind(int32_t n = 1);
			   void				moveAhead(const Symbol *s);
			  std::string			toString();
			  int32_t  getCurrentIndex();
			  void replaceSymbol(int32_t index, Symbol *s);
			   void deleteAll(symbol_type type);
			   void pushBack(const Symbol *);


		private:
			 bool				isEOF();
			 void				init(std::string str);




		};//end class

	}//end core
}//end obaro















/*########################################################IMPLEMENTATION SECTION ##################################################*/


#endif




