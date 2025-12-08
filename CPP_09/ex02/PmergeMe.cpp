#include "PmergeMe.hpp"
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>
#include <cstddef>

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

static std::vector<std::size_t> jacobsthal_order(std::size_t m) {
	std::vector<std::size_t> order;
	if (m == 0)
		return order;

	std::vector<std::size_t> J;
	J.push_back(0);
	J.push_back(1);
	while (true) {
		std::size_t next = J[J.size() - 1] + (2 * J[J.size() - 2]);
		if (next > m)
			break;
		J.push_back(next);
	}

	std::vector<char> used(m, false);
	std::size_t k = 1;
	while (k < J.size()) {
		if (J[k] >= 1 && J[k] <= m) {
			std::size_t idx = J[k] - 1;
			if (!used[idx]) {
				order.push_back(idx);
				used[idx] = true;
			}
		}
		++k;
	}

	std::size_t i = 0;
	while (i < m) {
		if (!used[i])
			order.push_back(i);
		++i;
	}
	return order;
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

	std::vector<std::size_t> order = jacobsthal_order(pairs.size());
	std::size_t idx = 0;
	while (idx < order.size()) {
		binaryInsertVector(mainChain, pairs[order[idx]].first);
		++idx;
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

	std::vector<std::size_t> order = jacobsthal_order(pairs.size());
	std::size_t j = 0;
	while (j < order.size()) {
		binaryInsertDeque(mainChain, pairs[order[j]].first);
		++j;
	}

	if (pending >= 0)
		binaryInsertDeque(mainChain, pending);
	return mainChain;
}
