/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
template <class Base>
DynamicFactory<Base>::DynamicFactory() : classnameInstantiatorTable_()
{
}


/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */
template <class Base>
DynamicFactory<Base>::~DynamicFactory()
{
}


/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */
template <class Base>
Base* DynamicFactory<Base>::CreateInstance(std::string classname)
{
	auto classnameInstantiatorTableIt = classnameInstantiatorTable_.find(classname);

	if(classnameInstantiatorTableIt != classnameInstantiatorTable_.end())
		return classnameInstantiatorTableIt->second->CreateInstance();
	else
		return nullptr;
}


/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */
template <class Base>
void DynamicFactory<Base>::RegisterClass(std::string classname, AbstractInstantiator<Base>* instantiator)
{
	classnameInstantiatorTable_[classname] = instantiator;
}


/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */
template <class Base>
template <class Derived>
void DynamicFactory<Base>::RegisterClass(std::string classname)
{
	AbstractInstantiator<Base>* instantiator = new Instantiator<Base, Derived>;
	classnameInstantiatorTable_[classname] = instantiator;
}


/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */
template <class Base>
void DynamicFactory<Base>::UnregisterClass(std::string classname)
{
	auto classnameInstantiatorTableIt = classnameInstantiatorTable_.find(classname);

	if(classnameInstantiatorTableIt != classnameInstantiatorTable_.end())
		classnameInstantiatorTable_.erase(classnameInstantiatorTableIt);
}


/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */
template <class Base>
bool DynamicFactory<Base>::isClass(std::string classname)
{
	if(classnameInstantiatorTable_.find(classname) != classnameInstantiatorTable_.end())
		return true;
	else
		return false;
}

/*! \brief
 *
 * \return size_t
 *
 */
template <class Base>
size_t DynamicFactory<Base>::getDynamicFactoryHash()
{
	return typeid(Base).hash_code();
}
