#ifndef UNIPAX_COMMON_SINGLETON_H
#define UNIPAX_COMMON_SINGLETON_H

#include<boost/shared_ptr.hpp>

namespace UniPAX
{

template <class T>
class Singleton
{
public:
	static Singleton& getInstance(T* obj)
	{
		boost::shared_ptr<T> tmp(obj);
		static Singleton<T> instance(tmp); // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	T* get() const
	{
		return object.get();
	}

private:
	Singleton(boost::shared_ptr<T> obj) : object(obj) {};

	Singleton(Singleton const &);
	void operator=(Singleton const &);

	boost::shared_ptr<T> object;
};

} // namespace end

#endif /* UNIPAX_COMMON_SINGLETON_H */
