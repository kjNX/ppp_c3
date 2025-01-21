#include <iostream>
#include <fstream>
#include <mutex>
#include <queue>
#include <thread>
#include <random>
#include "taglib/tag.h"
#include "taglib/fileref.h"

constexpr const char* const& AUDIO_PATH{"audio.flac"};
constexpr int ARRAY_SIZE{10000};
constexpr int UPPER_LIMIT{1024};

std::queue<std::string> g_names{};
std::mutex g_queueMutex{};

int g_currentSize{true};
bool g_sorted{true};
std::array<int, ARRAY_SIZE> g_array{};
std::mutex g_sortMutex{};

std::random_device g_rd{};
std::seed_seq g_seq{g_rd(), g_rd(), g_rd(), g_rd()};
std::ranlux48 g_randomGen{g_seq};
std::uniform_int_distribution<int> g_distribution{0, UPPER_LIMIT};

void intProvider()
{
	while(true)
	{
		std::unique_lock<std::mutex> lock{g_sortMutex};
		if(g_sorted)
		{
			g_sorted = false;
			g_currentSize = 0;
			lock.unlock();
			for(int& i : g_array)
			{
				std::scoped_lock lock{g_sortMutex};
				i = g_distribution(g_randomGen);
				++g_currentSize;
			}
		} else lock.unlock();
	}
}

void insertionSort()
{
	while(true)
	{
		int i{1};
		while(true)
		{
			std::scoped_lock lock{g_sortMutex};
			for(; i < g_currentSize; ++i)
				for(int j{i}, k{i - 1}; k >= 0 && g_array[k] > g_array[j]; j = k, --k)
				std::swap(g_array[k], g_array[j]);
			if(g_currentSize >= ARRAY_SIZE) break;
		}
	}
}

void idleCalculator()
{
	while(true)
	{
		int a{g_distribution(g_randomGen)}, b{g_distribution(g_randomGen)};
		std::cout << a << " + " << b << " = " << a + b << '\n';
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	}
}

void titleWrite()
{
	TagLib::FileRef ref{AUDIO_PATH};
	TagLib::String title{ref.tag() -> title()};
	TagLib::String artist{ref.tag() -> artist()};
	while(true)
	{
		std::printf("You are listening to %s by %s!\n", title.toCString(), artist.toCString());
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	}
}

void shoutOut()
{
	while(true)
	{
		std::scoped_lock queueLock{g_queueMutex};
		if(g_names.size() >= 3)
		{
			std::cout << "A huge shout-out to " << g_names.front() << ", ";
			g_names.pop();
			std::cout << g_names.front() << " and ";
			g_names.pop();
			std::cout << g_names.front() << "!\n";
			g_names.pop();
		}
	}
}

void greeter()
{
	std::string temp{};
	while(true)
	{
		std::cout << "Please enter your name.\n> ";
		std::cin >> temp;
		std::cout << "Hello, " << temp << "!\n";
		std::scoped_lock queueLock{g_queueMutex};
		g_names.push(temp);
	}
}

int main(int argc, char** argv)
{
	std::jthread thread1{intProvider};
	std::jthread thread2{insertionSort};
	std::jthread thread3{idleCalculator};
	std::jthread thread4{titleWrite};
	std::jthread thread5{greeter};
	std::jthread thread6{shoutOut};
	return 0;
}