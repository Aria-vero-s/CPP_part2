#include "RPN.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

RPN::RPN() {}
RPN::~RPN() {}

static bool isOperator(const std::string &tok) {
	if (tok.size() != 1)
		return false;
	char c = tok[0];
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	return false;
}

static bool parseNumber(const std::string &tok, long &value) {
	if (tok.empty())
		return false;
	size_t i = 0;
	while (i < tok.size()) {
		if (!std::isdigit(static_cast<unsigned char>(tok[i])))
			return false;
		i++;
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
				return false;
			long b = stack.back();
			stack.pop_back();
			long a = stack.back();
			stack.pop_back();
			long res = 0;
			switch (token[0]) {
				case '+': res = a + b; break;
				case '-': res = a - b; break;
				case '*': res = a * b; break;
				case '/':
					if (b == 0)
						return false;
					res = a / b;
					break;
				default:
					return false;
			}
			stack.push_back(res);
			continue;
		}
		return false;
	}

	if (stack.size() != 1)
		return false;
	result = stack.back();
	return true;
}
