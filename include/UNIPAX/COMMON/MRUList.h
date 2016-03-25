/*
 * MRU list implementation based on the Boost.MultiIndex example of serialization of a MRU list.
 * author: niermann
 */

#ifndef UNIPAX_MRULIST_H
#define UNIPAX_MRULIST_H

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <iterator>
#include <string>
#include <utility>

namespace UniPAX {

using namespace boost::multi_index;

template <typename Key, typename Value>
class MRUList
{
	struct Item
	{
		Key key;
		Value value;
		Item(Key k, Value v) : key(k), value(v) {}
	};

	typedef multi_index_container<
			Item,
			indexed_by<
				sequenced<>,
				hashed_unique<member<Item, Key, &Item::key> >
			>
	> item_list;

public:
	typedef Item                         item_type;
	typedef typename item_list::iterator iterator;

	MRUList(std::size_t max_num_items_):max_num_items(max_num_items_){}

	void insert(const Key& key, const Value& value)
	{
		item_type item(key, value);
		std::pair<iterator,bool> p=il.push_front(item);

		if(!p.second){                     /* duplicate item */
			il.relocate(il.begin(),p.first); /* put in front */
		}
		else if(il.size()>max_num_items){  /* keep the length <= max_num_items */
			il.pop_back();
		}
	}

	bool get(const Key &key, Value &value)
	{
		typename item_list::template nth_index<1>::type& hash_index=il.template get<1>();
#ifdef __GXX_EXPERIMENTAL_CXX0X__
		decltype( hash_index.begin()) it=hash_index.find(key);
#else
		typeof( hash_index.begin()) it=hash_index.find(key);
#endif
		if (it==hash_index.end()) return false;
		value=it->value;

		typename item_list::template nth_index<0>::type& sequenced_index=il.template get<0>();
#ifdef __GXX_EXPERIMENTAL_CXX0X__
		decltype(sequenced_index.begin()) it2=il.project<0>(it);
#else
    typeof(sequenced_index.begin()) it2=il.project<0>(it);
#endif
		sequenced_index.relocate(it2, sequenced_index.begin());

		return true;
	}

	iterator begin(){return il.begin();}
	iterator end(){return il.end();}

private:
	item_list   il;
	std::size_t max_num_items;
};
} // end namespace UniPAX
#endif
