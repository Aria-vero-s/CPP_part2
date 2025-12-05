#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Use: ./btc <input_file>" << std::endl;
		return 1;
	}
	BitcoinExchange btc;
	bool ok = btc.loadDatabase("data.csv");
	if (!ok) {
		std::cerr << "Error: could not open file data.csv" << std::endl;
		return 1;
	}
	btc.processInput(argv[1]);
	return 0;
}
