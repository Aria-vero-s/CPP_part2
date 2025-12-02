#include <iostream>
#include <vector>
#include <ctime>

#include "Span.hpp"

int main()
{
	{
		Span sp(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		try {
			std::cout << sp.shortestSpan() << std::endl;
			std::cout << sp.longestSpan() << std::endl;
		}
		catch (const std::exception & e) {
			std::cout << e.what() << std::endl;
		}
	}
	{
		Span big(10000);
		std::vector<int> numbers;
		numbers.reserve(10000);
		for (int i = 0; i < 10000; ++i)
			numbers.push_back(i * 2);

		try {
			big.addNumber(numbers.begin(), numbers.end());
			std::cout << "Big shortestSpan: " << big.shortestSpan() << std::endl; // should be 2
			std::cout << "Big longestSpan: " << big.longestSpan() << std::endl;   // should be (19998)
		}
		catch (const std::exception & e) {
			std::cout << e.what() << std::endl;
		}
	}
	{
		Span small(3);
		try {
			small.addNumber(1);
			small.addNumber(2);
			small.addNumber(3);
			// this throws
			small.addNumber(4);
		}
		catch (const std::exception & e) {
			std::cout << "Expected exception: " << e.what() << std::endl;
		}
	}
	return 0;
}
