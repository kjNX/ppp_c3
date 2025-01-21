#include <cstdio>
#include <thread>
#include <unistd.h>

void cpu_waster()
{
	printf("CPU Waster PID: %d\n", getpid());
	printf("CPU Waster Thread ID: %u\n", std::this_thread::get_id());
	while(true);
}

int main()
{
	printf("Main Process ID: %d\n", getpid());
	printf("Main Thread Thread ID: %u\n", std::this_thread::get_id());
	std::jthread thread1{cpu_waster};
	std::jthread thread2{cpu_waster};
}