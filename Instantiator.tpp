/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */
template <class Base, class Derived>
Derived* Instantiator<Base, Derived>::CreateInstance()
{
	return new Derived;
}
