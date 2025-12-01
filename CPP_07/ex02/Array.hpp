#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <iostream>

template<typename T>
class Array {
public:
	Array();
	explicit Array(unsigned int n);
	Array(Array const & other);
	Array & operator=(Array const & other);
	~Array();

	T & operator[](unsigned int idx);
	T const & operator[](unsigned int idx) const;

	unsigned int size() const;

	class IndexOutOfBounds : public std::exception {
	public:
		virtual const char* what() const throw();
	};

private:
	T * _data;
	unsigned int _size;
};

#include "Array.tpp"

#endif
