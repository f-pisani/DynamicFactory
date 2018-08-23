#ifndef INSTANTIATOR_HPP_INCLUDED
#define INSTANTIATOR_HPP_INCLUDED

#include "AbstractInstantiator.hpp"

template <class Base, class Derived>
class Instantiator : public AbstractInstantiator<Base>
{
	public:
		Derived* CreateInstance();
};

#include "Instantiator.tpp"

#endif // INSTANTIATOR_HPP_INCLUDED
