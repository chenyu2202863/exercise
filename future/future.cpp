// future.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <future>
#include <thread>

using namespace std::literals::chrono_literals;
int main()
{
	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::thread([p = std::move(p)]() mutable 
	{
		std::this_thread::sleep_for(5s);
		p.set_value_at_thread_exit(9);
	}).detach();

	std::cout << "Waiting..." << std::flush;
	f.wait();
	std::cout << "Done!\nResult is: " << f.get() << '\n';
	system("pause");
	return 0;
}

