
#ifndef CORE_COMPARABLE_H
#define CORE_COMPARABLE_H
#ifdef JCORE_EXPORTS
#define CORE_COMPARABLE_API __declspec(dllexport) 
#else
#define CORE_COMPARABLE_API __declspec(dllimport)
#endif

/*Comments
This is the base template class interface for object comparing.
*/

namespace obaro
{

	namespace core
	{
		template<class E> class __declspec(dllexport) Comparable
		{
		protected:
			 Comparable();
			~Comparable();

		public:
			//the virual method that will compare the objects
			 bool compareTo(E e);
		};


	}//end of the core namespace

}//end of  the obaro namespace


//implementations

using namespace obaro::core;

//constructor
template<class E>
Comparable<E>::Comparable()
{

}
//destructor
template<class E>
Comparable<E>::~Comparable()
{

}

#endif