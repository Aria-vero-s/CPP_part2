#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class PmergeMe {
public:
	PmergeMe();
	~PmergeMe();

	static std::vector<int> sortVector(const std::vector<int> &input);
	static std::deque<int> sortDeque(const std::vector<int> &input);
};

#endif