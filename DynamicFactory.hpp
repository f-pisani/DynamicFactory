#ifndef DYNAMICFACTORY_HPP_INCLUDED
#define DYNAMICFACTORY_HPP_INCLUDED

#include <typeinfo>
#include <typeindex>
#include <map>
#include "Instantiator.hpp"

template <class Base>
class DynamicFactory
{
	public:
		DynamicFactory();
		~DynamicFactory();

		template <class Derived> void RegisterClass(std::string classname);
		void RegisterClass(std::string classname, AbstractInstantiator<Base>* instantiator);
		void UnregisterClass(std::string classname);
		Base* CreateInstance(std::string classname);

		bool isClass(std::string classname);
		size_t getDynamicFactoryHash();

	private:
		std::map<std::string, AbstractInstantiator<Base>*> classnameInstantiatorTable_;
};

#include "DynamicFactory.tpp"

#endif // DYNAMICFACTORY_HPP_INCLUDED
