#include "RPN.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

RPN::RPN() {}
RPN::~RPN() {}

static bool isOperator(const std::string &tok) {
	return tok.size() == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/');
}

static bool parseNumber(const std::string &tok, long &value) {
	if (tok.empty()) return false;
	for (size_t i = 0; i < tok.size(); ++i) {
		if (!std::isdigit(static_cast<unsigned char>(tok[i])))
			return false;
	}
	std::istringstream ss(tok);
	ss >> value;
	return !ss.fail();
}

bool RPN::evaluate(const std::string &expr, long &result) const {
	std::istringstream ss(expr);
	std::string token;
	std::vector<long> stack;

	while (ss >> token) {
		long val;
		if (parseNumber(token, val)) {
			stack.push_back(val);
			continue;
		}

		if (isOperator(token)) {
			if (stack.size() < 2)
				return false; // not enough operands
			long b = stack.back(); stack.pop_back();
			long a = stack.back(); stack.pop_back();
			long res = 0;
			switch (token[0]) {
				case '+': res = a + b; break;
				case '-': res = a - b; break;
				case '*': res = a * b; break;
				case '/':
					if (b == 0) return false; // division by zero
					res = a / b; // integer division
					break;
				default:
					return false;
			}
			stack.push_back(res);
			continue;
		}

		// token is neither a number nor an operator -> error
		return false;
	}

	if (stack.size() != 1) return false;
	result = stack.back();
	return true;
}
