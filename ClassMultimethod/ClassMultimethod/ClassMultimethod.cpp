#include <functional>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <utility>


template<class Base, class Result, bool Commutative>
struct Multimethod2
{
	using Foo = std::function<Result(Base*, Base*)>;
	typedef std::type_index index;

	void addImpl(const std::type_info& t1, const std::type_info& t2, Foo f)
	{
		index i1(t1), i2(t2);
		myMap.emplace(std::move(make_pair(i1, i2)), std::move(f));
	}

	bool hasImpl(Base* a, Base* b) const
	{
		index i1(typeid(*a)), i2(typeid(*b));
		auto iter = myMap.find(make_pair(i1, i2));
		if (iter != myMap.end()) {
			return true;
		}
		if (Commutative) {
			std::swap(i1, i2);
			auto iter = myMap.find(make_pair(i1, i2));
			if (iter != myMap.end()) {
				return true;
			}
		}
		return false;
	}

	Result call(Base* a, Base* b) const
	{
		index i1(typeid(*a)), i2(typeid(*b));
		auto iter = myMap.find(make_pair(i1, i2));
		if (myMap.end() != iter) {
			return iter->second(a, b);
		}
		if (Commutative) {
			std::swap(i1, i2);
			auto iter = myMap.find(make_pair(i1, i2));
			if (myMap.end() != iter) {
				return iter->second(b, a);
			}
		}
	}

	std::map<std::pair<index, index>, Foo> myMap;
};