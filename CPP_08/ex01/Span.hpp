#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <iterator>
#include <exception>

class Span {
public:
	explicit Span(unsigned int N);
	Span(Span const & other);
	Span & operator=(Span const & other);
	~Span();

	void addNumber(int value);

	template <typename InputIt>
	void addNumber(InputIt first, InputIt last) {
		typename std::iterator_traits<InputIt>::difference_type dist = std::distance(first, last);
		if (dist < 0)
			throw FullException();
		if (_data.size() + static_cast<size_t>(dist) > _maxSize)
			throw FullException();
		_data.insert(_data.end(), first, last);
	}

	long shortestSpan() const;
	long longestSpan() const;

	unsigned int getMaxSize() const;
	size_t size() const;

	class FullException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class NotEnoughElementsException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

private:
	unsigned int _maxSize;
	std::vector<int> _data;
};

#endif