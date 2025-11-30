#include "functions.hpp"

int main() {
	std::srand(static_cast<unsigned int>(std::time(0)));

    Base* ptr = generate();
    
    std::cout << "Identify by pointer: ";
    identify(ptr);
    
    std::cout << "Identify by reference: ";
    identify(*ptr);

    delete ptr;
    return 0;
}
