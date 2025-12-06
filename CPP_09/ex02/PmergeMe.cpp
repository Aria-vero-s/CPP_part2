#include "PmergeMe.hpp"
#include <algorithm>
#include <utility>

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

static void binaryInsertVector(std::vector<int> &v, int value) {
	std::vector<int>::iterator it = std::lower_bound(v.begin(), v.end(), value);
	v.insert(it, value);
}

static void binaryInsertDeque(std::deque<int> &d, int value) {
	std::deque<int>::iterator it = std::lower_bound(d.begin(), d.end(), value);
	d.insert(it, value);
}

static bool pairCompare(const std::pair<int,int> &p1, const std::pair<int,int> &p2) {
	return p1.second < p2.second;
}

std::vector<int> PmergeMe::sortVector(const std::vector<int> &input) {
	std::size_t n = input.size();

	if (n <= 1)
		return std::vector<int>(input.begin(), input.end());

	std::vector< std::pair<int,int> > pairs;
	int pending = -1;
	std::size_t i = 0;

	while (i < n) {
		if (i + 1 < n) {
			int a = input[i];
			int b = input[i + 1];
			if (a <= b)
				pairs.push_back(std::make_pair(a, b));
			else
				pairs.push_back(std::make_pair(b, a));
			i += 2;
		}
		else {
			pending = input[i];
			i += 1;
		}
	}

	std::sort(pairs.begin(), pairs.end(), pairCompare);
	std::vector<int> mainChain;

	if (pending >= 0)
		mainChain.reserve(pairs.size() + 1);
	else
		mainChain.reserve(pairs.size());
	i = 0;
	while (i < pairs.size()) {
		mainChain.push_back(pairs[i].second);
		++i;
	}
	i = 0;
	while (i < pairs.size()) {
		binaryInsertVector(mainChain, pairs[i].first);
		++i;
	}
	if (pending >= 0)
		binaryInsertVector(mainChain, pending);
	return mainChain;
}

std::deque<int> PmergeMe::sortDeque(const std::vector<int> &input) {
	std::size_t n = input.size();
	if (n <= 1)
		return std::deque<int>(input.begin(), input.end());

	std::vector< std::pair<int,int> > pairs;
	int pending = -1;
	std::size_t i = 0;
	while (i < n) {
		if (i + 1 < n) {
			int a = input[i];
			int b = input[i + 1];
			if (a <= b)
				pairs.push_back(std::make_pair(a, b));
			else
				pairs.push_back(std::make_pair(b, a));
			i += 2;
		}
		else {
			pending = input[i];
			i += 1;
		}
	}
	std::sort(pairs.begin(), pairs.end(), pairCompare);
	std::deque<int> mainChain;
	i = 0;
	while (i < pairs.size()) {
		mainChain.push_back(pairs[i].second);
		++i;
	}
	i = 0;
	while (i < pairs.size()) {
		binaryInsertDeque(mainChain, pairs[i].first);
		++i;
	}
	if (pending >= 0)
		binaryInsertDeque(mainChain, pending);
	return mainChain;
}
