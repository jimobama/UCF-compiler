
#ifndef PROPERTIES_CORE_H
#define PROPERTIES_CORE_H


#ifdef JCORE_EXPORTS
#define PROPERTIES_CORE_API __declspec(dllexport) 
#else
#define PROPERTIES_CORE_API __declspec(dllimport)
#endif


template<class _Prop_t, class _ObjClass_t>
class  __declspec(dllexport)  Property
{
	typedef _Prop_t(_ObjClass_t::* _pmGet_t)() const;
	typedef void (_ObjClass_t::* _pmSet_t)(_Prop_t);

	_ObjClass_t& m_objInstance;
	_pmGet_t     m_pmGet;
	_pmSet_t     m_pmSet;

public:
	Property(_ObjClass_t& objInstance, _pmGet_t pmGet, _pmSet_t pmSet)
		: m_objInstance(objInstance), m_pmGet(pmGet), m_pmSet(pmSet)
	{}
	operator _Prop_t() { return (m_objInstance.*m_pmGet)(); }
	void operator =(_Prop_t value) { (m_objInstance.*m_pmSet)(value); }
};



#endif