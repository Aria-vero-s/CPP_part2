#ifndef ITER_HPP
#define ITER_HPP

template< typename T, typename F >
void iter(T *array, unsigned int length, F func)
{
	unsigned int i = 0;
	while (i < length)
	{
		func(array[i]);
		++i;
	}
}

#endif