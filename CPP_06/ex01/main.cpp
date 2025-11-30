#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
	Data d;
	d.n = 1337;
	d.c = 'A';
	d.s = "hello";

	Data* p = &d;
	std::cout << "Original pointer: " << p << std::endl;

	uintptr_t raw = Serializer::serialize(p);
	std::cout << "Serialized (numeric): " << static_cast<unsigned long long>(raw) << std::endl;

	Data* p2 = Serializer::deserialize(raw);
	std::cout << "Deserialized pointer: " << p2 << std::endl;

	if (p == p2)
		std::cout << "Success: pointers are equal" << std::endl;
	else
		std::cout << "Error: pointers differ" << std::endl;

	std::cout << "Data through deserialized pointer: " << p2->n << ", " << p2->c << ", " << p2->s << std::endl;

	return 0;
}