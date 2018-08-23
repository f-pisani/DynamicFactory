#ifndef ABSTRACTINSTANTIATOR_HPP_INCLUDED
#define ABSTRACTINSTANTIATOR_HPP_INCLUDED

template<class Base>
class AbstractInstantiator
{
	public:
		virtual Base* CreateInstance() = 0;
};

#endif // ABSTRACTINSTANTIATOR_HPP_INCLUDED
