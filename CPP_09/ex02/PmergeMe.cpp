#include "PmergeMe.hpp"
#include <algorithm>
#include <utility>

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

// Helper: binary-insert int value into sorted vector
static void binaryInsertVector(std::vector<int> &v, int value) {
	std::vector<int>::iterator it = std::lower_bound(v.begin(), v.end(), value);
	v.insert(it, value);
}

// Helper: binary-insert int value into sorted deque
static void binaryInsertDeque(std::deque<int> &d, int value) {
	std::deque<int>::iterator it = std::lower_bound(d.begin(), d.end(), value);
	d.insert(it, value);
}

std::vector<int> PmergeMe::sortVector(const std::vector<int> &input) {
	std::size_t n = input.size();
	if (n <= 1) return std::vector<int>(input.begin(), input.end());

	// Create pairs (min, max)
	std::vector< std::pair<int,int> > pairs;
	int pending = -1;
	for (std::size_t i = 0; i < n; i += 2) {
		if (i + 1 < n) {
			int a = input[i];
			int b = input[i+1];
			if (a <= b) pairs.push_back(std::make_pair(a,b)); else pairs.push_back(std::make_pair(b,a));
		} else {
			pending = input[i];
		}
	}

	// Sort pairs by their max (second)
	std::sort(pairs.begin(), pairs.end(),
		&[](const std::pair<int,int> &p1, const std::pair<int,int> &p2) -> bool {
			return p1.second < p2.second;
		}
	);

	// main chain = all max elements in order
	std::vector<int> mainChain;
	mainChain.reserve(pairs.size() + (pending >= 0 ? 1 : 0));
	for (std::size_t i = 0; i < pairs.size(); ++i)
		mainChain.push_back(pairs[i].second);

	// Insert minima (pairs[i].first) into mainChain using binary insertion
	for (std::size_t i = 0; i < pairs.size(); ++i) {
		binaryInsertVector(mainChain, pairs[i].first);
	}

	// Insert pending element if exists
	if (pending >= 0) binaryInsertVector(mainChain, pending);

	return mainChain;
}

std::deque<int> PmergeMe::sortDeque(const std::vector<int> &input) {
	std::size_t n = input.size();
	if (n <= 1) return std::deque<int>(input.begin(), input.end());

	// Create pairs (min, max)
	std::vector< std::pair<int,int> > pairs;
	int pending = -1;
	for (std::size_t i = 0; i < n; i += 2) {
		if (i + 1 < n) {
			int a = input[i];
			int b = input[i+1];
			if (a <= b) pairs.push_back(std::make_pair(a,b)); else pairs.push_back(std::make_pair(b,a));
		} else {
			pending = input[i];
		}
	}

	// Sort pairs by their max (second)
	std::sort(pairs.begin(), pairs.end(),
		&[](const std::pair<int,int> &p1, const std::pair<int,int> &p2) -> bool {
			return p1.second < p2.second;
		}
	);

	// main chain = all max elements in order
	std::deque<int> mainChain;
	for (std::size_t i = 0; i < pairs.size(); ++i)
		mainChain.push_back(pairs[i].second);

	// Insert minima (pairs[i].first) into mainChain using binary insertion
	for (std::size_t i = 0; i < pairs.size(); ++i) {
		binaryInsertDeque(mainChain, pairs[i].first);
	}

	// Insert pending element if exists
	if (pending >= 0) binaryInsertDeque(mainChain, pending);

	return mainChain;
}
