#include <iostream>
#include <thread>

void cpu_waster(const std::string& str) { while(1) std::printf("%s\n", str.c_str()); }

int main()
{
	std::jthread thread1{cpu_waster, "Hello!"};
	std::jthread thread2{cpu_waster, "Goodbye!"};
}
