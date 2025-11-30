#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(ScalarConverter const&);
		ScalarConverter& operator=(ScalarConverter const&);

	public:
		static void convert(std::string const& literal);
};

#endif