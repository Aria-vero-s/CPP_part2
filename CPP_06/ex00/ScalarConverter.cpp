#include "ScalarConverter.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cfloat>
#include <cmath>
#include <limits>
#include <cctype>

enum Type { T_INVALID, T_CHAR, T_INT, T_FLOAT, T_DOUBLE, T_PSEUDO };

static bool isPseudoLiteral(const std::string& s) {
	return (s == "nan"  || s == "nanf" ||
			s == "+inf" || s == "+inff" ||
			s == "-inf" || s == "-inff");
}

static bool isCharLiteral(const std::string& s) {
	if (s.size() != 1)
		return false;
	char c = s[0];
	if (std::isdigit(static_cast<unsigned char>(c)))
		return false;
	return true;
}

static bool isIntLiteral(const std::string& s) {
	std::size_t i = 0;
	if (s.empty())
		return false;
	if (s[i] == '+' || s[i] == '-')
		++i;
	if (i == s.size())
		return false;
	while (i < s.size()) {
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
			return false;
		++i;
	}
	return true;
}

static bool isFloatLiteral(const std::string& s) {
	if (s.size() < 2)
		return false;
	if (s[s.size() - 1] != 'f')
		return false;
	std::string core = s.substr(0, s.size() - 1);
	char* endptr = NULL;
	errno = 0;
	std::strtod(core.c_str(), &endptr);
	bool isValid = true;
	if (endptr == core.c_str())
		isValid = false;
	else if (*endptr != '\0')
		isValid = false;
	else if (errno != 0)
		isValid = false;
	return isValid;
}

static bool isDoubleLiteral(const std::string& s) {
	if (s.empty())
		return false;
	if (s[s.size() - 1] == 'f')
		return false;
	char* endptr = NULL;
	errno = 0;
	std::strtod(s.c_str(), &endptr);
	if (endptr == s.c_str())
		return false;
	if (*endptr != '\0')
		return false;
	if (errno != 0)
		return false;
	return true;
}

Type detectType(const std::string& s) {
	if (isPseudoLiteral(s))
		return T_PSEUDO;
	if (isCharLiteral(s))
		return T_CHAR;
	if (isIntLiteral(s))
		return T_INT;
	if (isFloatLiteral(s))
		return T_FLOAT;
	if (isDoubleLiteral(s))
		return T_DOUBLE;
	return T_INVALID;
}

void printChar(double value) {
	std::cout << "char: ";
	if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max()) {
		std::cout << "impossible" << std::endl;
		return;
	}
	char c = static_cast<char>(value);
	if (!std::isprint(static_cast<unsigned char>(c))) {
		std::cout << "Non displayable" << std::endl;
		return;
	}
	std::cout << '\'' << c << '\'' << std::endl;
}

void printInt(double value) {
	std::cout << "int: ";
	if (std::isnan(value) || std::isinf(value) || value < static_cast<double>(INT_MIN) || value > static_cast<double>(INT_MAX)) {
		std::cout << "impossible" << std::endl;
		return;
	}
	int i = static_cast<int>(value);
	std::cout << i << std::endl;
}

void printFloat(double value) {
	std::cout << "float: ";
	if (std::isnan(value)) {
		std::cout << "nanf" << std::endl;
		return;
	}
	if (std::isinf(value)) {
		if (value < 0)
			std::cout << "-inff" << std::endl;
		else
			std::cout << "+inff" << std::endl;
		return;
	}
	float f = static_cast<float>(value);
	if (value < -FLT_MAX || value > FLT_MAX) {
		std::cout << "impossible" << std::endl;
		return;
	}
	std::ostringstream oss;
	if (std::floor(f) == f)
		oss << std::fixed << std::setprecision(1) << f << 'f';
	else
		oss << f << 'f';
	std::cout << oss.str() << std::endl;
}

void printDouble(double value) {
	std::cout << "double: ";
	if (std::isnan(value)) {
		std::cout << "nan" << std::endl;
		return;
	}
	if (std::isinf(value)) {
		if (value < 0)
			std::cout << "-inf" << std::endl;
		else
			std::cout << "+inf" << std::endl;
		return;
	}
	std::ostringstream oss;
	if (std::floor(value) == value)
		oss << std::fixed << std::setprecision(1) << value;
	else
		oss << value;
	std::cout << oss.str() << std::endl;
}

void ScalarConverter::convert(std::string const& s) {
	Type t = detectType(s);

	if (t == T_INVALID) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	double value = 0.0;

	if (t == T_PSEUDO) {
		if (s == "nan" || s == "nanf")
			value = std::numeric_limits<double>::quiet_NaN();
		else if (s == "+inf" || s == "+inff")
			value = std::numeric_limits<double>::infinity();
		else if (s == "-inf" || s == "-inff")
			value = -std::numeric_limits<double>::infinity();
	}
	else if (t == T_CHAR)
		value = static_cast<double>(s[0]);
	else if (t == T_INT) {
		char* endptr = NULL;
		errno = 0;
		long tmp = std::strtol(s.c_str(), &endptr, 10);
		if (errno != 0 || *endptr != '\0' || tmp < INT_MIN || tmp > INT_MAX) {
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return;
		}
		value = static_cast<double>(tmp);
	}
	else if (t == T_FLOAT) {
		std::string core = s.substr(0, s.size() - 1);
		char* endptr = NULL;
		errno = 0;
		double tmp = std::strtod(core.c_str(), &endptr);
		if (errno != 0 || *endptr != '\0') {
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return;
		}
		value = tmp;
	}
	else if (t == T_DOUBLE) {
		char* endptr = NULL;
		errno = 0;
		double tmp = std::strtod(s.c_str(), &endptr);
		if (errno != 0 || *endptr != '\0') {
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return;
		}
		value = tmp;
	}

	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
