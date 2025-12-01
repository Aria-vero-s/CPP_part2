#include "Span.hpp"
#include <algorithm>
#include <limits>

Span::Span(unsigned int N): _maxSize(N), _data() {}

Span::Span(Span const & other): _maxSize(other._maxSize), _data(other._data) {}

Span & Span::operator=(Span const & other) {
	if (this != &other) {
		_maxSize = other._maxSize;
		_data = other._data;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int value) {
	if (_data.size() >= _maxSize)
		throw FullException();
	_data.push_back(value);
}

long Span::shortestSpan() const {
	if (_data.size() < 2)
		throw NotEnoughElementsException();

	std::vector<int> tmp(_data);
	std::sort(tmp.begin(), tmp.end());

	long minDiff = std::numeric_limits<long>::max();
	size_t i = 1;
	while (i < tmp.size()) {
		long diff = static_cast<long>(tmp[i]) - static_cast<long>(tmp[i - 1]);
		if (diff < minDiff)
			minDiff = diff;
		++i;
	}
	return minDiff;
}

long Span::longestSpan() const {
	if (_data.size() < 2)
		throw NotEnoughElementsException();

	std::vector<int>::const_iterator minIt = std::min_element(_data.begin(), _data.end());
	std::vector<int>::const_iterator maxIt = std::max_element(_data.begin(), _data.end());
	return static_cast<long>(*maxIt) - static_cast<long>(*minIt);
}

unsigned int Span::getMaxSize() const { return _maxSize; }

size_t Span::size() const { return _data.size(); }

const char* Span::FullException::what() const throw() {
	return "Span: cannot add number(s) — container is full";
}

const char* Span::NotEnoughElementsException::what() const throw() {
	return "Span: not enough elements to find a span";
}
