#include <iostream>
#include <thread>
#include <limits>

int intQuery()
{
	int result{};
	std::cout << "Enter an integer.\n> ";
starter:
	std::cin >> result;
	if(!std::cin)
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.clear();
		std::cout << "Please enter an integer.\n> ";
		goto starter;
	}
	return result;
}

void cpu_waster()
{
	while(true)
	{
		const int& a{intQuery()};
		const int& b{intQuery()};
		std::cout << a << " + " << b << " = " << a + b << '\n';
	}
}

int main()
{
	std::jthread thread1{cpu_waster};
	std::jthread thread2{cpu_waster};
}
