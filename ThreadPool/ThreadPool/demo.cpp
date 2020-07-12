#include <iostream>
#include "ThreadPool.hpp"

using namespace std;

void TestThread()
{
	ThreadPool pool;
	std::thread thd1([&pool] {
		for (int i = 0; i < 10; ++i)
		{
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId] {cout << "ͬ���߳�1���߳�Id:" << thdId << endl; });
	}
	});
	std::thread thd2([&pool] {
		for (int i = 0; i < 10; ++i)
		{
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId] {cout << "ͬ���߳�2���߳�Id:" << thdId << endl; });
		}
	});
	this_thread::sleep_for(std::chrono::seconds(1));
	getchar();
	pool.Stop();
	thd1.join();
	thd2.join();
}

int main()
{
	TestThread();
	getchar();
	return 0;
}