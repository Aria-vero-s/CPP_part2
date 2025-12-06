#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <sstream>
#include <sys/time.h>
#include <iomanip>

static bool parseArgs(int argc, char **argv, std::vector<int> &out)
{
	if (argc < 2)
		return false;
	int i = 1;
	while (i < argc)
	{
		std::string s(argv[i]);
		if (s.empty())
			return false;
		size_t j = 0;
		while (j < s.size())
		{
			if (!std::isdigit(static_cast<unsigned char>(s[j])))
				return false;
			++j;
		}
		long v = std::strtol(s.c_str(), NULL, 10);
		if (v <= 0)
			return false;
		out.push_back(static_cast<int>(v));
		++i;
	}
	return true;
}

static double timeval_diff_us(const struct timeval &start, const struct timeval &end) {
	double s = start.tv_sec + start.tv_usec / 1000000.0;
	double e = end.tv_sec + end.tv_usec / 1000000.0;
	return (e - s) * 1e6;
}

int main(int argc, char **argv) {
	std::vector<int> input;
	if (!parseArgs(argc, argv, input)) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	std::cout << "Before: ";
	size_t i = 0;
	while (i < input.size()) {
		if (i)
			std::cout << ' ';
		std::cout << input[i];
		++i;
	}
	std::cout << std::endl;
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
	std::vector<int> sortedVec = PmergeMe::sortVector(input);
	gettimeofday(&t2, NULL);
	double timeVecUs = timeval_diff_us(t1, t2);
	gettimeofday(&t1, NULL);
	std::deque<int> sortedDeq = PmergeMe::sortDeque(input);
	gettimeofday(&t2, NULL);
	double timeDeqUs = timeval_diff_us(t1, t2);
	std::cout << "After: ";
	i = 0;
	while (i < sortedVec.size()) {
		if (i)
			std::cout << ' ';
		std::cout << sortedVec[i];
		++i;
	}
	std::cout << std::endl;
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << input.size() << " elements with std::vector : " << timeVecUs << " us" << std::endl;
	std::cout << "Time to process a range of " << input.size() << " elements with std::deque  : " << timeDeqUs << " us" << std::endl;
	return 0;
}
