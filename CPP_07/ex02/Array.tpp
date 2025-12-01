#ifndef ARRAY_TPP
#define ARRAY_TPP

template<typename T>
Array<T>::Array() : _data(NULL), _size(0) {}

template<typename T>
Array<T>::Array(unsigned int n) : _data(NULL), _size(n) {
	if (n == 0) {
		_data = NULL;
		return;
	}
	_data = new T[n]();
}

template<typename T>
Array<T>::Array(Array const & other) : _data(NULL), _size(0) {
	if (other._size == 0) {
		_data = NULL;
		_size = 0;
		return;
	}
	_data = new T[other._size]();
	_size = other._size;
	unsigned int i = 0;
	while (i < _size) {
		_data[i] = other._data[i];
		++i;
	}
}

template<typename T>
Array<T> & Array<T>::operator=(Array const & other) {
	if (this == &other)
		return *this;

	T * newData = NULL;
	if (other._size > 0) {
		newData = new T[other._size]();
		unsigned int i = 0;
		while (i < other._size) {
			newData[i] = other._data[i];
			++i;
		}
	}

	delete [] _data;
	_data = newData;
	_size = other._size;
	return *this;
}

template<typename T>
Array<T>::~Array() {
	delete [] _data;
}

template<typename T>
T & Array<T>::operator[](unsigned int idx) {
	if (idx >= _size)
		throw IndexOutOfBounds();
	return _data[idx];
}

template<typename T>
T const & Array<T>::operator[](unsigned int idx) const {
	if (idx >= _size)
		throw IndexOutOfBounds();
	return _data[idx];
}

template<typename T>
unsigned int Array<T>::size() const {
	return _size;
}

template<typename T>
const char* Array<T>::IndexOutOfBounds::what() const throw() {
	return "Array: index out of bounds";
}

#endif
