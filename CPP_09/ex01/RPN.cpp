#include "RPN.hpp"
#include <sstream>
#include <string>
#include <stack>
#include <cctype>

RPN::RPN() {}
RPN::~RPN() {}

static bool isOperator(const std::string &tok) {
	if (tok.size() != 1)
		return false;
	char c = tok[0];
	return (c == '+' || c == '-' || c == '*' || c == '/');
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
	std::stack<long> st;

	while (ss >> token) {
		long val;
		if (parseNumber(token, val)) {
			st.push(val);
			continue;
		}
		if (isOperator(token)) {
			if (st.size() < 2)
				return false;
			long b = st.top();
			st.pop();
			long a = st.top();
			st.pop();
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
			st.push(res);
			continue;
		}
		return false;
	}

	if (st.size() != 1)
		return false;
	result = st.top();
	return true;
}
