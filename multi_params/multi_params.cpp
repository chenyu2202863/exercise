// multi_params.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

#include <tuple>
#include <iostream>
#include <array>
#include <utility>


template<class Cont, class Tup, std::size_t... Is>
void emplace_back_impl(Cont& c, const Tup& tup, std::index_sequence<Is...>)
{
	using swallow = int[];
	(void) swallow
	{
		0, (void(c.emplace_back(std::get<Is>(tup))), 0)...
	};
}

template<class Cont, class ...Args>
void emplace_multiple(Cont& c, const std::tuple<Args...> &tups)
{
	emplace_back_impl(c, tups, std::make_index_sequence<sizeof...(Args)>{});
}

int main()
{
	std::vector<std::uint8_t> m = {0, 1, 2};
	emplace_multiple(m, std::make_tuple(1, 2, 3));
	for(const auto &v:m )
		std::cout << (std::uint32_t)v << " ";

	system("pause");
    return 0;
}



template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch, Tr>& os,
	const Tuple & t,
	std::index_sequence<Is...>)
{
	using swallow = int[]; // guaranties left to right order
	(void) swallow
	{
		0, (void(os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), 0)...
	};
}

template<class Ch, class Tr, class... Args>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os,
	const std::tuple<Args...>& t)
{
	os << "(";
	print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
	return os << ")";
}

//int main()
//{
//	std::array<int, 4> array = { 1,2,3,4 };
//
//	// convert an array into a tuple
//	auto tuple = a2t(array);
//	static_assert(std::is_same<decltype(tuple),
//		std::tuple<int, int, int, int>>::value, "");
//
//	// print it to cout
//	std::cout << tuple << '\n';
//}